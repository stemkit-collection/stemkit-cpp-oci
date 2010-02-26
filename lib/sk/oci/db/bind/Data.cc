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

static const sk::util::String __className("sk::oci::db::bind::Data");

sk::oci::db::bind::Data::
Data(uint32_t position, ub2 type, uint32_t value)
  : _position(position), _type(type), _indicator(0), 
    _value(reinterpret_cast<const char*>(&value), reinterpret_cast<const char*>(&value) + sizeof(value))
{
  _handle.oci_define = 0;
  _handle.oci_bind = 0;
}

sk::oci::db::bind::Data::
Data(uint32_t position, ub2 type, int size, const sk::util::String& value)
  : _position(position), _type(type), _indicator(0), 
    _value(size, 0)
{
  _handle.oci_define = 0;
  _handle.oci_bind = 0;

  std::copy(value.begin(), value.begin() + std::min(size, value.size()), _value.begin());
}

sk::oci::db::bind::Data::
~Data()
{
}

const sk::util::Class
sk::oci::db::bind::Data::
getClass() const
{
  return sk::util::Class(__className);
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

uint32_t 
sk::oci::db::bind::Data::
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
