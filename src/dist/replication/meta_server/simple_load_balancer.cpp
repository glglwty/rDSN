/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Microsoft Corporation
 * 
 * -=- Robust Distributed System Nucleus (rDSN) -=- 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * Description:
 *     What is this file about?
 *
 * Revision history:
 *     xxxx-xx-xx, author, first version
 *     xxxx-xx-xx, author, fix bug about xxx
 */

#include "simple_load_balancer.h"
#include <algorithm>

# ifdef __TITLE__
# undef __TITLE__
# endif
# define __TITLE__ "load.balancer"

simple_load_balancer::simple_load_balancer(server_state* state):
    ::dsn::dist::server_load_balancer(state),
    serverlet<simple_load_balancer>("simple_load_balancer")
{
}

simple_load_balancer::~simple_load_balancer()
{
}

void simple_load_balancer::run()
{
    if (s_disable_lb) return;

    zauto_read_lock l(_state->_lock);

    for (size_t i = 0; i < _state->_apps.size(); i++)
    {
        app_state& app = _state->_apps[i];
        if (app.info.status != app_status::AS_AVAILABLE)
            continue;

        if (_state->freezed() && app.info.is_stateful)
            continue;

        for (int j = 0; j < app.info.partition_count; j++)
        {
            partition_configuration& pc = app.partitions[j];
            run_lb(app.info, pc, app.info.is_stateful);
        }
    }
}

void simple_load_balancer::run(gpid gpid)
{
    if (s_disable_lb) return;

    zauto_read_lock l(_state->_lock);
    partition_configuration& pc = _state->_apps[gpid.get_app_id() - 1].partitions[gpid.get_partition_index()];
    run_lb(_state->_apps[gpid.get_app_id() - 1].info, pc, _state->_apps[gpid.get_app_id() - 1].info.is_stateful);
}

::dsn::rpc_address simple_load_balancer::find_minimal_load_machine(bool primaryOnly)
{
    std::vector<std::pair< ::dsn::rpc_address, int>> stats;

    for (auto it = _state->_nodes.begin(); it != _state->_nodes.end(); ++it)
    {
        if (it->second.is_alive)
        {
            stats.push_back(std::make_pair(it->first, static_cast<int>(primaryOnly ? it->second.primaries.size()
                : it->second.partitions.size())));
        }
    }

    if (stats.empty())
    {
        return ::dsn::rpc_address();
    }
    
    std::sort(stats.begin(), stats.end(), [](const std::pair< ::dsn::rpc_address, int>& l, const std::pair< ::dsn::rpc_address, int>& r)
    {
        return l.second < r.second || (l.second == r.second && l.first < r.first);
    });

    if (s_lb_for_test)
    {
        // alway use the first (minimal) one
        return stats[0].first;
    }

    int candidate_count = 1;
    int val = stats[0].second;

    for (size_t i = 1; i < stats.size(); i++)
    {
        if (stats[i].second > val)
            break;
        candidate_count++;
    }

    return stats[dsn_random32(0, candidate_count - 1)].first;
}

void simple_load_balancer::run_lb(app_info& info, partition_configuration& pc, bool is_stateful)
{
    if (_state->freezed() && is_stateful)
        return;

    configuration_update_request proposal;
    proposal.config = pc;
    proposal.info = info;

    if (is_stateful)
    {
        if (pc.primary.is_invalid())
        {
            if (pc.secondaries.size() > 0)
            {
                if (s_lb_for_test)
                {
                    std::vector< ::dsn::rpc_address> tmp(pc.secondaries);
                    std::sort(tmp.begin(), tmp.end());
                    proposal.node = tmp[0];
                }
                else
                {
                    proposal.node = pc.secondaries[dsn_random32(0, static_cast<int>(pc.secondaries.size()) - 1)];
                }
                proposal.type = config_type::CT_UPGRADE_TO_PRIMARY;
            }

            else if (pc.last_drops.size() == 0)
            {
                proposal.node = find_minimal_load_machine(true);
                proposal.type = config_type::CT_ASSIGN_PRIMARY;
            }

            // DDD
            else
            {
                proposal.node = *pc.last_drops.rbegin();
                proposal.type = config_type::CT_ASSIGN_PRIMARY;

                derror("%s.%d.%d enters DDD state, we are waiting for its last primary node %s to come back ...",
                    info.app_type.c_str(),
                    pc.pid.get_app_id(),
                    pc.pid.get_partition_index(),
                    proposal.node.to_string()
                    );
            }

            if (proposal.node.is_invalid() == false)
            {
                send_proposal(proposal.node, proposal);
            }
        }

        else if (static_cast<int>(pc.secondaries.size()) + 1 < pc.max_replica_count)
        {
            proposal.type = config_type::CT_ADD_SECONDARY;
            proposal.node = find_minimal_load_machine(false);
            if (proposal.node.is_invalid() == false &&
                proposal.node != pc.primary &&
                std::find(pc.secondaries.begin(), pc.secondaries.end(), proposal.node) == pc.secondaries.end())
            {
                send_proposal(pc.primary, proposal);
            }
        }
        else
        {
            // it is healthy, nothing to do
        }
    }
    
    // stateless
    else
    {
        partition_configuration_stateless pcs(pc);

        if (static_cast<int>(pcs.worker_replicas().size()) < pc.max_replica_count)
        {
            proposal.type = config_type::CT_ADD_SECONDARY;
            proposal.node = find_minimal_load_machine(false);
            if (proposal.node.is_invalid() == false)
            {
                bool send = true;

                for (auto& s : pc.secondaries)
                {
                    // not on the same machine
                    if (s == proposal.node)
                    {
                        send = false;
                        break;
                    }
                }

                if (send)
                {
                    send_proposal(proposal.node, proposal);
                }
            }
        }
        else
        {
            // it is healthy, nothing to do
        }
    }
}

void simple_load_balancer::query_decree(std::shared_ptr<query_replica_decree_request> query)
{
    rpc::call(
        query->node,
        RPC_QUERY_PN_DECREE,
        *query,
        this,
        [this, query](error_code err, query_replica_decree_response&& resp) 
        {
            auto response = std::make_shared<query_replica_decree_response>(std::move(resp));
            on_query_decree_ack(err, query, response);
        }
        ,
        gpid_to_hash(query->pid), std::chrono::seconds(3));
}

void simple_load_balancer::on_query_decree_ack(error_code err, const std::shared_ptr<query_replica_decree_request>& query, const std::shared_ptr<query_replica_decree_response>& resp)
{
    if (err != ERR_OK)
    {
        tasking::enqueue(LPC_QUERY_PN_DECREE, this, std::bind(&simple_load_balancer::query_decree, this, query), 0, std::chrono::seconds(1));
    }
    else
    {
        zauto_write_lock l(_state->_lock);
        app_state& app = _state->_apps[query->pid.get_app_id() - 1];
        partition_configuration& ps = app.partitions[query->pid.get_partition_index()];
        if (resp->last_decree > ps.last_committed_decree)
        {
            ps.last_committed_decree = resp->last_decree;
        }   
    }
}
