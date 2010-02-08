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

#include <sk/oci/ErrorException.h>

static const sk::util::String __className("sk::oci::ErrorException");

sk::oci::ErrorException::
ErrorException(const sk::util::String& origin, int code, const sk::util::String& message)
  : sk::oci::Exception(origin, message), _code(code)
{
}

const sk::util::Class
sk::oci::ErrorException::
getClass() const
{
  return sk::util::Class(__className);
}

int
sk::oci::ErrorException::
getCode() const
{
  return _code;
}
