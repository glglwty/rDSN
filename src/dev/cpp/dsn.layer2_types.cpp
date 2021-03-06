/**
 * Autogenerated by Thrift Compiler (@PACKAGE_VERSION@)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "dsn.layer2_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>

namespace dsn {

int _kapp_statusValues[] = {
  app_status::AS_INVALID,
  app_status::AS_AVAILABLE,
  app_status::AS_CREATING,
  app_status::AS_CREATE_FAILED,
  app_status::AS_DROPPING,
  app_status::AS_DROP_FAILED,
  app_status::AS_DROPPED
};
const char* _kapp_statusNames[] = {
  "AS_INVALID",
  "AS_AVAILABLE",
  "AS_CREATING",
  "AS_CREATE_FAILED",
  "AS_DROPPING",
  "AS_DROP_FAILED",
  "AS_DROPPED"
};
const std::map<int, const char*> _app_status_VALUES_TO_NAMES(::apache::thrift::TEnumIterator(7, _kapp_statusValues, _kapp_statusNames), ::apache::thrift::TEnumIterator(-1, NULL, NULL));


partition_configuration::~partition_configuration() throw() {
}


void partition_configuration::__set_pid(const  ::dsn::gpid& val) {
  this->pid = val;
}

void partition_configuration::__set_ballot(const int64_t val) {
  this->ballot = val;
}

void partition_configuration::__set_max_replica_count(const int32_t val) {
  this->max_replica_count = val;
}

void partition_configuration::__set_primary(const  ::dsn::rpc_address& val) {
  this->primary = val;
}

void partition_configuration::__set_secondaries(const std::vector< ::dsn::rpc_address> & val) {
  this->secondaries = val;
}

void partition_configuration::__set_last_drops(const std::vector< ::dsn::rpc_address> & val) {
  this->last_drops = val;
}

void partition_configuration::__set_last_committed_decree(const int64_t val) {
  this->last_committed_decree = val;
}

uint32_t partition_configuration::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->pid.read(iprot);
          this->__isset.pid = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->ballot);
          this->__isset.ballot = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->max_replica_count);
          this->__isset.max_replica_count = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->primary.read(iprot);
          this->__isset.primary = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->secondaries.clear();
            uint32_t _size0;
            ::apache::thrift::protocol::TType _etype3;
            xfer += iprot->readListBegin(_etype3, _size0);
            this->secondaries.resize(_size0);
            uint32_t _i4;
            for (_i4 = 0; _i4 < _size0; ++_i4)
            {
              xfer += this->secondaries[_i4].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.secondaries = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 6:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->last_drops.clear();
            uint32_t _size5;
            ::apache::thrift::protocol::TType _etype8;
            xfer += iprot->readListBegin(_etype8, _size5);
            this->last_drops.resize(_size5);
            uint32_t _i9;
            for (_i9 = 0; _i9 < _size5; ++_i9)
            {
              xfer += this->last_drops[_i9].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.last_drops = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 7:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->last_committed_decree);
          this->__isset.last_committed_decree = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t partition_configuration::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("partition_configuration");

  xfer += oprot->writeFieldBegin("pid", ::apache::thrift::protocol::T_STRUCT, 1);
  xfer += this->pid.write(oprot);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("ballot", ::apache::thrift::protocol::T_I64, 2);
  xfer += oprot->writeI64(this->ballot);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("max_replica_count", ::apache::thrift::protocol::T_I32, 3);
  xfer += oprot->writeI32(this->max_replica_count);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("primary", ::apache::thrift::protocol::T_STRUCT, 4);
  xfer += this->primary.write(oprot);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("secondaries", ::apache::thrift::protocol::T_LIST, 5);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->secondaries.size()));
    std::vector< ::dsn::rpc_address> ::const_iterator _iter10;
    for (_iter10 = this->secondaries.begin(); _iter10 != this->secondaries.end(); ++_iter10)
    {
      xfer += (*_iter10).write(oprot);
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("last_drops", ::apache::thrift::protocol::T_LIST, 6);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->last_drops.size()));
    std::vector< ::dsn::rpc_address> ::const_iterator _iter11;
    for (_iter11 = this->last_drops.begin(); _iter11 != this->last_drops.end(); ++_iter11)
    {
      xfer += (*_iter11).write(oprot);
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("last_committed_decree", ::apache::thrift::protocol::T_I64, 7);
  xfer += oprot->writeI64(this->last_committed_decree);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(partition_configuration &a, partition_configuration &b) {
  using ::std::swap;
  swap(a.pid, b.pid);
  swap(a.ballot, b.ballot);
  swap(a.max_replica_count, b.max_replica_count);
  swap(a.primary, b.primary);
  swap(a.secondaries, b.secondaries);
  swap(a.last_drops, b.last_drops);
  swap(a.last_committed_decree, b.last_committed_decree);
  swap(a.__isset, b.__isset);
}

partition_configuration::partition_configuration(const partition_configuration& other12) {
  pid = other12.pid;
  ballot = other12.ballot;
  max_replica_count = other12.max_replica_count;
  primary = other12.primary;
  secondaries = other12.secondaries;
  last_drops = other12.last_drops;
  last_committed_decree = other12.last_committed_decree;
  __isset = other12.__isset;
}
partition_configuration& partition_configuration::operator=(const partition_configuration& other13) {
  pid = other13.pid;
  ballot = other13.ballot;
  max_replica_count = other13.max_replica_count;
  primary = other13.primary;
  secondaries = other13.secondaries;
  last_drops = other13.last_drops;
  last_committed_decree = other13.last_committed_decree;
  __isset = other13.__isset;
  return *this;
}
void partition_configuration::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "partition_configuration(";
  out << "pid=" << to_string(pid);
  out << ", " << "ballot=" << to_string(ballot);
  out << ", " << "max_replica_count=" << to_string(max_replica_count);
  out << ", " << "primary=" << to_string(primary);
  out << ", " << "secondaries=" << to_string(secondaries);
  out << ", " << "last_drops=" << to_string(last_drops);
  out << ", " << "last_committed_decree=" << to_string(last_committed_decree);
  out << ")";
}


configuration_query_by_index_request::~configuration_query_by_index_request() throw() {
}


void configuration_query_by_index_request::__set_app_name(const std::string& val) {
  this->app_name = val;
}

void configuration_query_by_index_request::__set_partition_indices(const std::vector<int32_t> & val) {
  this->partition_indices = val;
}

uint32_t configuration_query_by_index_request::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->app_name);
          this->__isset.app_name = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->partition_indices.clear();
            uint32_t _size14;
            ::apache::thrift::protocol::TType _etype17;
            xfer += iprot->readListBegin(_etype17, _size14);
            this->partition_indices.resize(_size14);
            uint32_t _i18;
            for (_i18 = 0; _i18 < _size14; ++_i18)
            {
              xfer += iprot->readI32(this->partition_indices[_i18]);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.partition_indices = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t configuration_query_by_index_request::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("configuration_query_by_index_request");

  xfer += oprot->writeFieldBegin("app_name", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->app_name);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("partition_indices", ::apache::thrift::protocol::T_LIST, 2);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_I32, static_cast<uint32_t>(this->partition_indices.size()));
    std::vector<int32_t> ::const_iterator _iter19;
    for (_iter19 = this->partition_indices.begin(); _iter19 != this->partition_indices.end(); ++_iter19)
    {
      xfer += oprot->writeI32((*_iter19));
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(configuration_query_by_index_request &a, configuration_query_by_index_request &b) {
  using ::std::swap;
  swap(a.app_name, b.app_name);
  swap(a.partition_indices, b.partition_indices);
  swap(a.__isset, b.__isset);
}

configuration_query_by_index_request::configuration_query_by_index_request(const configuration_query_by_index_request& other20) {
  app_name = other20.app_name;
  partition_indices = other20.partition_indices;
  __isset = other20.__isset;
}
configuration_query_by_index_request& configuration_query_by_index_request::operator=(const configuration_query_by_index_request& other21) {
  app_name = other21.app_name;
  partition_indices = other21.partition_indices;
  __isset = other21.__isset;
  return *this;
}
void configuration_query_by_index_request::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "configuration_query_by_index_request(";
  out << "app_name=" << to_string(app_name);
  out << ", " << "partition_indices=" << to_string(partition_indices);
  out << ")";
}


configuration_query_by_index_response::~configuration_query_by_index_response() throw() {
}


void configuration_query_by_index_response::__set_err(const  ::dsn::error_code& val) {
  this->err = val;
}

void configuration_query_by_index_response::__set_app_id(const int32_t val) {
  this->app_id = val;
}

void configuration_query_by_index_response::__set_partition_count(const int32_t val) {
  this->partition_count = val;
}

void configuration_query_by_index_response::__set_is_stateful(const bool val) {
  this->is_stateful = val;
}

void configuration_query_by_index_response::__set_partitions(const std::vector<partition_configuration> & val) {
  this->partitions = val;
}

uint32_t configuration_query_by_index_response::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->err.read(iprot);
          this->__isset.err = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->app_id);
          this->__isset.app_id = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->partition_count);
          this->__isset.partition_count = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->is_stateful);
          this->__isset.is_stateful = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->partitions.clear();
            uint32_t _size22;
            ::apache::thrift::protocol::TType _etype25;
            xfer += iprot->readListBegin(_etype25, _size22);
            this->partitions.resize(_size22);
            uint32_t _i26;
            for (_i26 = 0; _i26 < _size22; ++_i26)
            {
              xfer += this->partitions[_i26].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.partitions = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t configuration_query_by_index_response::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("configuration_query_by_index_response");

  xfer += oprot->writeFieldBegin("err", ::apache::thrift::protocol::T_STRUCT, 1);
  xfer += this->err.write(oprot);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("app_id", ::apache::thrift::protocol::T_I32, 2);
  xfer += oprot->writeI32(this->app_id);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("partition_count", ::apache::thrift::protocol::T_I32, 3);
  xfer += oprot->writeI32(this->partition_count);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("is_stateful", ::apache::thrift::protocol::T_BOOL, 4);
  xfer += oprot->writeBool(this->is_stateful);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("partitions", ::apache::thrift::protocol::T_LIST, 5);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->partitions.size()));
    std::vector<partition_configuration> ::const_iterator _iter27;
    for (_iter27 = this->partitions.begin(); _iter27 != this->partitions.end(); ++_iter27)
    {
      xfer += (*_iter27).write(oprot);
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(configuration_query_by_index_response &a, configuration_query_by_index_response &b) {
  using ::std::swap;
  swap(a.err, b.err);
  swap(a.app_id, b.app_id);
  swap(a.partition_count, b.partition_count);
  swap(a.is_stateful, b.is_stateful);
  swap(a.partitions, b.partitions);
  swap(a.__isset, b.__isset);
}

configuration_query_by_index_response::configuration_query_by_index_response(const configuration_query_by_index_response& other28) {
  err = other28.err;
  app_id = other28.app_id;
  partition_count = other28.partition_count;
  is_stateful = other28.is_stateful;
  partitions = other28.partitions;
  __isset = other28.__isset;
}
configuration_query_by_index_response& configuration_query_by_index_response::operator=(const configuration_query_by_index_response& other29) {
  err = other29.err;
  app_id = other29.app_id;
  partition_count = other29.partition_count;
  is_stateful = other29.is_stateful;
  partitions = other29.partitions;
  __isset = other29.__isset;
  return *this;
}
void configuration_query_by_index_response::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "configuration_query_by_index_response(";
  out << "err=" << to_string(err);
  out << ", " << "app_id=" << to_string(app_id);
  out << ", " << "partition_count=" << to_string(partition_count);
  out << ", " << "is_stateful=" << to_string(is_stateful);
  out << ", " << "partitions=" << to_string(partitions);
  out << ")";
}


app_info::~app_info() throw() {
}


void app_info::__set_status(const app_status::type val) {
  this->status = val;
}

void app_info::__set_app_type(const std::string& val) {
  this->app_type = val;
}

void app_info::__set_app_name(const std::string& val) {
  this->app_name = val;
}

void app_info::__set_app_id(const int32_t val) {
  this->app_id = val;
}

void app_info::__set_partition_count(const int32_t val) {
  this->partition_count = val;
}

void app_info::__set_envs(const std::map<std::string, std::string> & val) {
  this->envs = val;
}

void app_info::__set_is_stateful(const bool val) {
  this->is_stateful = val;
}

uint32_t app_info::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          int32_t ecast30;
          xfer += iprot->readI32(ecast30);
          this->status = (app_status::type)ecast30;
          this->__isset.status = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->app_type);
          this->__isset.app_type = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->app_name);
          this->__isset.app_name = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->app_id);
          this->__isset.app_id = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->partition_count);
          this->__isset.partition_count = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 6:
        if (ftype == ::apache::thrift::protocol::T_MAP) {
          {
            this->envs.clear();
            uint32_t _size31;
            ::apache::thrift::protocol::TType _ktype32;
            ::apache::thrift::protocol::TType _vtype33;
            xfer += iprot->readMapBegin(_ktype32, _vtype33, _size31);
            uint32_t _i35;
            for (_i35 = 0; _i35 < _size31; ++_i35)
            {
              std::string _key36;
              xfer += iprot->readString(_key36);
              std::string& _val37 = this->envs[_key36];
              xfer += iprot->readString(_val37);
            }
            xfer += iprot->readMapEnd();
          }
          this->__isset.envs = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 7:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->is_stateful);
          this->__isset.is_stateful = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t app_info::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("app_info");

  xfer += oprot->writeFieldBegin("status", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32((int32_t)this->status);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("app_type", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->app_type);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("app_name", ::apache::thrift::protocol::T_STRING, 3);
  xfer += oprot->writeString(this->app_name);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("app_id", ::apache::thrift::protocol::T_I32, 4);
  xfer += oprot->writeI32(this->app_id);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("partition_count", ::apache::thrift::protocol::T_I32, 5);
  xfer += oprot->writeI32(this->partition_count);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("envs", ::apache::thrift::protocol::T_MAP, 6);
  {
    xfer += oprot->writeMapBegin(::apache::thrift::protocol::T_STRING, ::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->envs.size()));
    std::map<std::string, std::string> ::const_iterator _iter38;
    for (_iter38 = this->envs.begin(); _iter38 != this->envs.end(); ++_iter38)
    {
      xfer += oprot->writeString(_iter38->first);
      xfer += oprot->writeString(_iter38->second);
    }
    xfer += oprot->writeMapEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("is_stateful", ::apache::thrift::protocol::T_BOOL, 7);
  xfer += oprot->writeBool(this->is_stateful);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(app_info &a, app_info &b) {
  using ::std::swap;
  swap(a.status, b.status);
  swap(a.app_type, b.app_type);
  swap(a.app_name, b.app_name);
  swap(a.app_id, b.app_id);
  swap(a.partition_count, b.partition_count);
  swap(a.envs, b.envs);
  swap(a.is_stateful, b.is_stateful);
  swap(a.__isset, b.__isset);
}

app_info::app_info(const app_info& other39) {
  status = other39.status;
  app_type = other39.app_type;
  app_name = other39.app_name;
  app_id = other39.app_id;
  partition_count = other39.partition_count;
  envs = other39.envs;
  is_stateful = other39.is_stateful;
  __isset = other39.__isset;
}
app_info& app_info::operator=(const app_info& other40) {
  status = other40.status;
  app_type = other40.app_type;
  app_name = other40.app_name;
  app_id = other40.app_id;
  partition_count = other40.partition_count;
  envs = other40.envs;
  is_stateful = other40.is_stateful;
  __isset = other40.__isset;
  return *this;
}
void app_info::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "app_info(";
  out << "status=" << to_string(status);
  out << ", " << "app_type=" << to_string(app_type);
  out << ", " << "app_name=" << to_string(app_name);
  out << ", " << "app_id=" << to_string(app_id);
  out << ", " << "partition_count=" << to_string(partition_count);
  out << ", " << "envs=" << to_string(envs);
  out << ", " << "is_stateful=" << to_string(is_stateful);
  out << ")";
}

} // namespace
