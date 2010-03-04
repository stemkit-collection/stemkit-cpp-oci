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

#include "IntData.h"

static const sk::util::String __className("sk::oci::db::bind::IntData");

sk::oci::db::bind::IntData::
IntData(int capacity, const sk::util::String& tag, const sk::util::Integers& values)
  : bind::Data(capacity, tag, SQLT_INT, sizeof(uint32_t))
{
  setValues(values);
}

sk::oci::db::bind::IntData::
IntData(int capacity, const sk::util::String& tag)
  : bind::Data(capacity, tag, SQLT_INT, sizeof(uint32_t))
{
}

sk::oci::db::bind::IntData::
IntData(int capacity, uint32_t position, const sk::util::Integers& values)
  : bind::Data(capacity, position, SQLT_INT, sizeof(uint32_t))
{
  setValues(values);
}

sk::oci::db::bind::IntData::
IntData(int capacity, uint32_t position)
  : bind::Data(capacity, position, SQLT_INT, sizeof(uint32_t))
{
}

const sk::util::Class
sk::oci::db::bind::IntData::
getClass() const
{
  return sk::util::Class(__className);
}

void
sk::oci::db::bind::IntData::
setValues(const sk::util::Integers& values)
{
  int expected = capacity();
  int size = values.size();

  if(size != expected) {
    throw sk::util::IllegalStateException("Wrong number of bind values: need " + sk::util::String::valueOf(expected) + ", got " + sk::util::String::valueOf(size));
  }
  for(int index=0; index < size; ++index) {
    setIntValue(index, values.get(index));
  }
}

const sk::util::String
sk::oci::db::bind::IntData::
toString(int index) const
{
  return isNull(index) ? "0" : sk::util::String::valueOf(intValue(index));
}

const sk::util::String
sk::oci::db::bind::IntData::
inspect(int index) const
{
  return isNull(index) ? "NULL" : sk::util::String::valueOf(intValue(index));
}
