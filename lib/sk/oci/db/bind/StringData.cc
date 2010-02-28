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

#include "StringData.h"

static const sk::util::String __className("sk::oci::db::bind::StringData");

sk::oci::db::bind::StringData::
StringData(uint32_t position, int size, const sk::util::String& value)
  : bind::Data(position, SQLT_STR, size)
{
  std::copy(value.begin(), value.begin() + std::min(size - 1, value.size()), stringValue().begin());
}

sk::oci::db::bind::StringData::
~StringData()
{
}

const sk::util::Class
sk::oci::db::bind::StringData::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String
sk::oci::db::bind::StringData::
toString() const
{
  return isNull() ? "" : stringValue().toString();
}

const sk::util::String
sk::oci::db::bind::StringData::
inspect() const
{
  return isNull() ? "NULL" : stringValue().toString().inspect();
}
