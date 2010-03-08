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

#include "Piece.h"
#include "Data.h"

static const sk::util::String __className("sk::oci::db::bind::Piece");

sk::oci::db::bind::Piece::
Piece(int index, bind::Data& data)
  : _index(index), _data(data)
{
}

sk::oci::db::bind::Piece::
~Piece()
{
}

const sk::util::Class
sk::oci::db::bind::Piece::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::oci::Data& 
sk::oci::db::bind::Piece::
piece(int index) const
{
  return _data.piece(index);
}

sk::oci::Data& 
sk::oci::db::bind::Piece::
piece(int index)
{
  return _data.piece(index);
}

const sk::util::String 
sk::oci::db::bind::Piece::
info() const
{
  return _data.info(_index);
}

const sk::util::String
sk::oci::db::bind::Piece::
toString() const
{
  return _data.toString(_index);
}

const sk::util::String
sk::oci::db::bind::Piece::
inspect() const
{
  return _data.inspect(_index);
}

const int32_t& 
sk::oci::db::bind::Piece::
intValue() const
{
  return _data.intValue(_index);
}

void 
sk::oci::db::bind::Piece::
setIntValue(int32_t value)
{
  _data.setIntValue(_index, value);
}

const char* 
sk::oci::db::bind::Piece::
charsValue() const
{
  return _data.charsValue(_index);
}

void 
sk::oci::db::bind::Piece::
setCharsValue(const sk::util::String& value)
{
  _data.setCharsValue(_index, value);
}

const sk::util::String 
sk::oci::db::bind::Piece::
stringValue() const
{
  return sk::util::String(_data.charsValue(_index), _data.size(_index));
}

bool 
sk::oci::db::bind::Piece::
isNull() const
{
  return _data.isNull(_index);
}

bool 
sk::oci::db::bind::Piece::
isTruncated() const
{
  return _data.isTruncated(_index);
}

uint32_t 
sk::oci::db::bind::Piece::
size() const
{
  return _data.size(_index);
}

uint32_t 
sk::oci::db::bind::Piece::
columnCode() const
{
  return _data.columnCode(_index);
}

void 
sk::oci::db::bind::Piece::
setNull(bool state)
{
  _data.setNull(_index, state);
}
