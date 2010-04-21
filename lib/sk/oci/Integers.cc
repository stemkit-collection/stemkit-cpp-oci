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

#include <sk/oci/Integers.h>
#include <sk/oci/Statement.h>
#include <sk/oci/Cursor.h>

static const sk::util::String __className("sk::oci::Integers");

sk::oci::Integers::
Integers()
{
}

sk::oci::Integers::
~Integers()
{
}

sk::oci::Integers&
sk::oci::Integers::
operator << (const uint32_t& item)
{
  addLast(item);
  return *this;
}

const sk::util::Class
sk::oci::Integers::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::oci::Integers::
bindTag(const sk::util::String& tag, sk::oci::Statement& statement) const
{
  statement.bindIntTag(tag, *this);
}

void 
sk::oci::Integers::
bindPosition(int position, sk::oci::Statement& statement) const
{
  statement.bindIntAt(position, *this);
}

int 
sk::oci::Integers::
bindPosition(int position, sk::oci::Cursor& cursor) const
{
  return cursor.bindIntAt(position);
}
