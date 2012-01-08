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

#include <sk/oci/StillExecutingException.h>

static const sk::util::String __className("sk::oci::StillExecutingException");

sk::oci::StillExecutingException::
StillExecutingException(const sk::util::String& origin)
  : sk::oci::Exception(origin, "Still executing")
{
}

const sk::util::Class
sk::oci::StillExecutingException::
getClass() const
{
  return sk::util::Class(__className);
}
