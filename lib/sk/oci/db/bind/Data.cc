/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/IllegalStateException.h>
#include <sk/util/StringArray.h>

#include "Data.h"

static const sk::util::String __className("sk::oci::db::bind::Data");

sk::oci::db::bind::Data::
Data(uint32_t position, ub2 type, int size)
  : _position(position), _type(type), _indicator(OCI_IND_NULL), _columnCode(0), _size(size)
{
  _value.resize(size, 0);

  _handle.oci_define = 0;
  _handle.oci_bind = 0;
}

const sk::util::Class
sk::oci::db::bind::Data::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String
sk::oci::db::bind::Data::
info() const
{
  sk::util::StringArray depot;
  depot << inspect();

  if(isTruncated() == true) {
    if(_indicator > 0) {
      depot << "truncated(" + sk::util::String::valueOf(_indicator - _size) + ")";
    }
    else {
      depot << "truncated";
    }
  }
  if(_columnCode != 0) {
    depot << "code(" + sk::util::String::valueOf(_columnCode) + ")";
  }
  return depot.join(":");
}

sk::oci::db::bind::Data::oci_bind_handle& 
sk::oci::db::bind::Data::
bindHandle()
{
  return _handle.oci_bind;
}

sk::oci::db::bind::Data::oci_define_handle& 
sk::oci::db::bind::Data::
defineHandle()
{
  return _handle.oci_define;
}

ub4 
sk::oci::db::bind::Data::
position() const
{
  return _position;
}

dvoid* 
sk::oci::db::bind::Data::
valuePointer()
{
  return _value.size() == 0 ? 0 : &_value.front();
}

sb4 
sk::oci::db::bind::Data::
valueSize() const
{
  return _value.size();
}

ub2 
sk::oci::db::bind::Data::
type() const
{
  return _type;
}

dvoid* 
sk::oci::db::bind::Data::
indicatorPointer()
{
  return &_indicator;
}

uint32_t
sk::oci::db::bind::Data::
getColumnCode() const
{
  return _columnCode;
}

ub2*
sk::oci::db::bind::Data::
columnCodePointer()
{
  return &_columnCode;
}

uint32_t
sk::oci::db::bind::Data::
getSize() const
{
  return _size;
}

ub2*
sk::oci::db::bind::Data::
sizePointer()
{
  return &_size;
}

const text* 
sk::oci::db::bind::Data::
tagPointer() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sb4 
sk::oci::db::bind::Data::
tagSize() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

uint32_t&
sk::oci::db::bind::Data::
intValue()
{
  if(_value.size() != sizeof(uint32_t)) {
    throw sk::util::IllegalStateException(SK_METHOD);
  }
  union data_map_t {
    char buffer[sizeof(uint32_t)];
    uint32_t value;
  };

  data_map_t* data = reinterpret_cast<data_map_t*>(&_value.front());
  return data->value;
}

const uint32_t&
sk::oci::db::bind::Data::
intValue() const
{
  if(_value.size() != sizeof(uint32_t)) {
    throw sk::util::IllegalStateException(SK_METHOD);
  }
  union data_map_t {
    char buffer[sizeof(uint32_t)];
    uint32_t value;
  };

  const data_map_t* data = reinterpret_cast<const data_map_t*>(&_value.front());
  return data->value;
}

sk::util::Container&
sk::oci::db::bind::Data::
stringValue()
{
  return _value;
}

const sk::util::Container&
sk::oci::db::bind::Data::
stringValue() const
{
  return _value;
}

bool 
sk::oci::db::bind::Data::
isNull() const
{
  return _indicator == -1;
}

bool 
sk::oci::db::bind::Data::
isTruncated() const
{
  return _indicator == -2 || _indicator > 0;
}
