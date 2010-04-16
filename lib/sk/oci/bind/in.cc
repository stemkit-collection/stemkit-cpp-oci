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

#include <sk/oci/bind/in.h>

static const sk::util::String __className("sk::oci::bind::in");

sk::oci::bind::in::
in()
{
}

sk::oci::bind::in::
~in()
{
}

const sk::util::Class
sk::oci::bind::in::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::oci::bind::in::
prepareStatement(sk::oci::Statement& statement) const
{
}

void 
sk::oci::bind::in::
processCursor(sk::oci::Cursor& cursor, sk::oci::bind::Data& data) const
{
}
