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

#include "StringData.h"

static const sk::util::String __className("sk::oci::db::bind::StringData");

sk::oci::db::bind::StringData::
StringData(int capacity, const sk::util::String& tag, int size, const sk::util::Strings& values)
  : bind::Data(capacity, tag, SQLT_STR, size)
{
  std::copy(values.first().begin(), values.first().begin() + std::min(size - 1, values.first().size()), stringValue().begin());
  null(false);
}

sk::oci::db::bind::StringData::
StringData(int capacity, const sk::util::String& tag, int size)
  : bind::Data(capacity, tag, SQLT_STR, size)
{
  null(true);
}

sk::oci::db::bind::StringData::
StringData(int capacity, uint32_t position, int size, const sk::util::Strings& values)
  : bind::Data(capacity, position, SQLT_STR, size)
{
  std::copy(values.first().begin(), values.first().begin() + std::min(size - 1, values.first().size()), stringValue().begin());
  null(false);
}

sk::oci::db::bind::StringData::
StringData(int capacity, uint32_t position, int size)
  : bind::Data(capacity, position, SQLT_STR, size)
{
  null(true);
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
  return isNull() ? "" : sk::util::String(stringValue().getChars(), size());
}

const sk::util::String
sk::oci::db::bind::StringData::
inspect() const
{
  return isNull() ? "NULL" : sk::util::String(stringValue().getChars(), size()).inspect(); 
}
