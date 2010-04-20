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

#include <sk/oci/Strings.h>
#include <sk/oci/Statement.h>

static const sk::util::String __className("sk::oci::Strings");

sk::oci::Strings::
Strings(int cap)
  : sk::util::CappedStrings(cap)
{
}

sk::oci::Strings::
Strings()
{
}

sk::oci::Strings::
~Strings()
{
}

const sk::util::Class
sk::oci::Strings::
getClass() const
{
  return sk::util::Class(__className);
}

sk::oci::Strings&
sk::oci::Strings::
operator << (const sk::util::String& item)
{
  addLast(item);
  return *this;
}

void 
sk::oci::Strings::
bindTag(const sk::util::String& tag, sk::oci::Statement& statement) const
{
  statement.bindCharsTag(tag, maxItemSize(), *this);
}

void 
sk::oci::Strings::
bindPosition(int position, sk::oci::Statement& statement) const
{
  statement.bindCharsAt(position, maxItemSize(), *this);
}
