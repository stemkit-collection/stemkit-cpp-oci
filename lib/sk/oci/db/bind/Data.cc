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
#include <sk/util/ArrayList.cxx>

#include "Data.h"

static const sk::util::String __className("sk::oci::db::bind::Data");

sk::oci::db::bind::Data::
Data(int capacity, uint32_t position, ub2 type, int size)
  : _position(position), _type(type), _pieceSize(size)
{
  setup(capacity);
}

sk::oci::db::bind::Data::
Data(int capacity, const sk::util::String& tag, ub2 type, int size)
  : _position(0), _type(type), _pieceSize(size)
{
  setup(capacity);

  _depot.insert(_depot.end(), tag.begin(), tag.end());
  _depot.push_back(0);
}

void 
sk::oci::db::bind::Data::
setup(int capacity)
{                   
  _capacity = std::max(1, capacity);

  for(int index=0; index < _capacity; ++index) {
    _pieces.add(new bind::Piece(index, *this));
  }
  _descriptors.resize(_capacity * 3, 0);
  _depot.resize(_pieceSize * _capacity, 0);

  std::fill_n(_descriptors.begin(), _capacity, OCI_IND_NULL);

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
    if(indicator(index) > 0) {
      depot << "truncated(" + sk::util::String::valueOf(indicator(index) - size(index)) + ")";
    }
    else {
      depot << "truncated";
    }
  }
  if(columnCode(index) != 0) {
    depot << "code(" + sk::util::String::valueOf(columnCode(index)) + ")";
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
  return _pieceSize == 0 ? 0 : &_depot[0];
}

sb4 
sk::oci::db::bind::Data::
valueSize() const
{
  return _pieceSize;
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
  return reinterpret_cast<sb2*>(&_descriptors[0]);
}

uint32_t
sk::oci::db::bind::Data::
columnCode(int index) const
{
  ub2 code = _descriptors[_capacity + index];
  return code;
}

ub2*
sk::oci::db::bind::Data::
columnCodePointer()
{
  return &_descriptors[_capacity];
}

uint32_t
sk::oci::db::bind::Data::
size(int index) const
{
  return _descriptors[_capacity*2 + index];
}

ub2*
sk::oci::db::bind::Data::
sizePointer()
{
  return &_descriptors[_capacity*2];
}

const text* 
sk::oci::db::bind::Data::
tagPointer() const
{
  if(tagSize() == 0) {
    throw sk::util::IllegalStateException("Bind tag not set");
  }
  return reinterpret_cast<const text*>(&_depot[_capacity * _pieceSize]);
}

sb4 
sk::oci::db::bind::Data::
tagSize() const
{
  int size = _depot.size() - (_pieceSize * _capacity);
  return size > 0 ? size - 1 : 0;
}

const uint32_t&
sk::oci::db::bind::Data::
intValue(int index) const
{
  if(_pieceSize != sizeof(uint32_t)) {
    throw sk::util::IllegalStateException(SK_METHOD);
  }
  union data_map_t {
    char buffer[sizeof(uint32_t)];
    uint32_t value;
  };

  const data_map_t* data = reinterpret_cast<const data_map_t*>(&_depot[_pieceSize * index]);
  return data->value;
}

void
sk::oci::db::bind::Data::
setIntValue(int index, uint32_t value)
{
  if(_pieceSize != sizeof(uint32_t)) {
    throw sk::util::IllegalStateException(SK_METHOD);
  }
  union data_map_t {
    char buffer[sizeof(uint32_t)];
    uint32_t value;
  };

  data_map_t* data = reinterpret_cast<data_map_t*>(&_depot[_pieceSize * index]);
  data->value = value;
  setSize(index, _pieceSize);
  setNull(index, false);
}

const char*
sk::oci::db::bind::Data::
charsValue(int index) const
{
  return &_depot[_pieceSize * index];
}

void
sk::oci::db::bind::Data::
setCharsValue(int index, const sk::util::String& value)
{
  int length = std::min(_pieceSize - 1, value.size());
  std::copy(value.begin(), value.begin() + length, &_depot[_pieceSize * index]);
  setSize(index, length + 1);
  setNull(index, false);
}

void 
sk::oci::db::bind::Data::
setSize(int index, uint32_t size)
{
  _descriptors[_capacity*2 + index] = size;
}

bool 
sk::oci::db::bind::Data::
isNull(int index) const
{
  return indicator(index) == OCI_IND_NULL;
}

void 
sk::oci::db::bind::Data::
setNull(int index, bool state)
{
  _descriptors[index] = (state == true ? OCI_IND_NULL : 0);
}

bool 
sk::oci::db::bind::Data::
isTruncated(int index) const
{
  sb2 value = indicator(index);
  return value == -2 || value > 0;
}

const sk::oci::Data& 
sk::oci::db::bind::Data::
piece(int index) const
{
  return _pieces.get(index);
}

sk::oci::Data& 
sk::oci::db::bind::Data::
piece(int index)
{
  return _pieces.getMutable(index);
}

sb2
sk::oci::db::bind::Data::
indicator(int index) const 
{
  return _descriptors[index];
}

int 
sk::oci::db::bind::Data::
descriptorSize() const
{
  return _descriptors.size();
}

int 
sk::oci::db::bind::Data::
depotSize() const
{
  return _depot.size();
}
