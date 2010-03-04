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
#include <sk/util/Strings.h>

#include "CharsData.h"

static const sk::util::String __className("sk::oci::db::bind::CharsData");

sk::oci::db::bind::CharsData::
CharsData(int capacity, const sk::util::String& tag, int size, const sk::util::Strings& values)
  : bind::Data(capacity, tag, SQLT_STR, size)
{
  setValues(values);
}

sk::oci::db::bind::CharsData::
CharsData(int capacity, const sk::util::String& tag, int size)
  : bind::Data(capacity, tag, SQLT_STR, size)
{
}

sk::oci::db::bind::CharsData::
CharsData(int capacity, uint32_t position, int size, const sk::util::Strings& values)
  : bind::Data(capacity, position, SQLT_STR, size)
{
  setValues(values);
}

sk::oci::db::bind::CharsData::
CharsData(int capacity, uint32_t position, int size)
  : bind::Data(capacity, position, SQLT_STR, size)
{
}

sk::oci::db::bind::CharsData::
~CharsData()
{
}

const sk::util::Class
sk::oci::db::bind::CharsData::
getClass() const
{
  return sk::util::Class(__className);
}

void
sk::oci::db::bind::CharsData::
setValues(const sk::util::Strings& values)
{
  int expected = capacity();
  int size = values.size();

  if(size != expected) {
    throw sk::util::IllegalStateException("Wrong number of bind values: need " + sk::util::String::valueOf(expected) + ", got " + sk::util::String::valueOf(size));
  }
  for(int index=0; index < size; ++index) {
    setCharsValue(index, values.get(index));
  }
}

const sk::util::String
sk::oci::db::bind::CharsData::
toString(int index) const
{
  return isNull(index) ? "" : sk::util::String(charsValue(index), size(index));
}

const sk::util::String
sk::oci::db::bind::CharsData::
inspect(int index) const
{
  return isNull(index) ? "NULL" : sk::util::String(charsValue(index), size(index)).inspect(); 
}
