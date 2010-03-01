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
IntData(int capacity, uint32_t position, uint32_t value)
  : bind::Data(capacity, position, SQLT_INT, sizeof(uint32_t))
{
  intValue() = value;
  *indicatorPointer() = 0;
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

const sk::util::String
sk::oci::db::bind::IntData::
toString() const
{
  return isNull() ? "0" : sk::util::String::valueOf(intValue());
}

const sk::util::String
sk::oci::db::bind::IntData::
inspect() const
{
  return isNull() ? "NULL" : sk::util::String::valueOf(intValue());
}
