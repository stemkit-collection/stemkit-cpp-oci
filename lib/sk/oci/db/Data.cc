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

#include "Data.h"

static const sk::util::String __className("sk::oci::db::Data");

sk::oci::db::Data::
Data(uint32_t capacity, uint32_t position, ub2 type, const void* value, int32_t size)
  : _position(position), _type(type), _indicator(0), 
    _value(reinterpret_cast<const char*>(value), reinterpret_cast<const char*>(value) + size)
{
  _handle.oci_define = 0;
  _handle.oci_bind = 0;
}

sk::oci::db::Data::
~Data()
{
}

const sk::util::Class
sk::oci::db::Data::
getClass() const
{
  return sk::util::Class(__className);
}

sk::oci::db::Data::oci_bind_handle& 
sk::oci::db::Data::
bindHandle()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::oci::db::Data::oci_define_handle& 
sk::oci::db::Data::
defineHandle()
{
  return _handle.oci_define;
}

ub4 
sk::oci::db::Data::
position() const
{
  return _position;
}

dvoid* 
sk::oci::db::Data::
valuePointer()
{
  return _value.size() == 0 ? 0 : &_value.front();
}

sb4 
sk::oci::db::Data::
valueSize() const
{
  return _value.size();
}

ub2 
sk::oci::db::Data::
type() const
{
  return _type;
}

dvoid* 
sk::oci::db::Data::
indicatorPointer()
{
  return &_indicator;
}

const text* 
sk::oci::db::Data::
tagPointer() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sb4 
sk::oci::db::Data::
tagSize() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

uint32_t 
sk::oci::db::Data::
intValue() const
{
  uint32_t value;
  if(_value.size() != sizeof(value)) {
    throw sk::util::IllegalStateException(SK_METHOD);
  }
  std::copy(_value.begin(), _value.end(), reinterpret_cast<char*>(&value));
  return value;
}

const std::vector<char>& 
sk::oci::db::Data::
stringValue() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool 
sk::oci::db::Data::
isNull() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

bool 
sk::oci::db::Data::
isTruncated() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
