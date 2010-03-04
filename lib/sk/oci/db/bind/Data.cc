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
#include <sk/util/Strings.h>

#include "Data.h"

static const sk::util::String __className("sk::oci::db::bind::Data");

sk::oci::db::bind::Data::
Data(int capacity, uint32_t position, ub2 type, int size)
  : _position(position), _type(type), _indicator(OCI_IND_NULL), _columnCode(0), _size(size),
    _piece(0, *this)
{
  setup(capacity);
}

sk::oci::db::bind::Data::
Data(int capacity, const sk::util::String& tag, ub2 type, int size)
  : _tag(tag), _type(type), _indicator(OCI_IND_NULL), _columnCode(0), _size(size),
    _piece(0, *this)
{
  setup(capacity);
}

void 
sk::oci::db::bind::Data::
setup(int capacity)
{                   
  _capacity = std::max(1, capacity);

  if(_capacity > 1) {
    throw sk::util::UnsupportedOperationException("array bind");
  }
  _value.resize(_size, 0);

  _handle.oci_define = 0;
  _handle.oci_bind = 0;
}

const sk::util::Class
sk::oci::db::bind::Data::
getClass() const
{
  return sk::util::Class(__className);
}

int 
sk::oci::db::bind::Data::
capacity() const
{
  return _capacity;
}

const sk::util::String
sk::oci::db::bind::Data::
info(int index) const
{
  sk::util::Strings depot;
  depot << inspect(index);

  if(isTruncated(index) == true) {
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

sb2* 
sk::oci::db::bind::Data::
indicatorPointer()
{
  return &_indicator;
}

uint32_t
sk::oci::db::bind::Data::
columnCode(int index) const
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
size(int index) const
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
  if(_tag.size() == 0) {
    throw sk::util::IllegalStateException("Bind tag not set");
  }
  return reinterpret_cast<const text*>(&_tag.front());
}

sb4 
sk::oci::db::bind::Data::
tagSize() const
{
  return _tag.size();
}

const uint32_t&
sk::oci::db::bind::Data::
intValue(int index) const
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

void
sk::oci::db::bind::Data::
setIntValue(int index, uint32_t value)
{
  if(_value.size() != sizeof(uint32_t)) {
    throw sk::util::IllegalStateException(SK_METHOD);
  }
  union data_map_t {
    char buffer[sizeof(uint32_t)];
    uint32_t value;
  };

  data_map_t* data = reinterpret_cast<data_map_t*>(&_value.front());
  data->value = value;
  setNull(index, false);
}

const char*
sk::oci::db::bind::Data::
charsValue(int index) const
{
  return _value.getChars();
}

void
sk::oci::db::bind::Data::
setCharsValue(int index, const sk::util::String& value)
{
  std::copy(value.begin(), value.begin() + std::min(_size - 1, value.size()), _value.begin());
  setNull(index, false);
}

bool 
sk::oci::db::bind::Data::
isNull(int index) const
{
  return _indicator == OCI_IND_NULL;
}

void 
sk::oci::db::bind::Data::
setNull(int index, bool state)
{
  _indicator = (state == true ? OCI_IND_NULL : 0);
}

bool 
sk::oci::db::bind::Data::
isTruncated(int index) const
{
  return _indicator == -2 || _indicator > 0;
}

const sk::oci::Data& 
sk::oci::db::bind::Data::
piece(int index) const
{
  if(index != 0) {
    throw sk::util::IllegalStateException("Index other than 0 not supported yet");
  }
  return _piece;
}

sk::oci::Data& 
sk::oci::db::bind::Data::
piece(int index)
{
  if(index != 0) {
    throw sk::util::IllegalStateException("Index other than 0 not supported yet");
  }
  return _piece;
}
