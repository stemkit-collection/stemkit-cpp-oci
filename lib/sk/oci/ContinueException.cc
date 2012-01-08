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

#include <sk/oci/ContinueException.h>

static const sk::util::String __className("sk::oci::ContinueException");

sk::oci::ContinueException::
ContinueException(const sk::util::String& origin)
  : sk::oci::Exception(origin, "Continue")
{
}

const sk::util::Class
sk::oci::ContinueException::
getClass() const
{
  return sk::util::Class(__className);
}
