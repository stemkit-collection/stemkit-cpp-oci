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

#include <sk/oci/Exception.h>

static const sk::util::String __className("sk::oci::Exception");

sk::oci::Exception::
Exception(int code, sk::util::String& message)
  : sk::util::Exception(message), _code(code), _message(message)
{
}

sk::oci::Exception::
~Exception() throw()
{
}

const sk::util::Class
sk::oci::Exception::
getClass() const
{
  return sk::util::Class(__className);
}

int
sk::oci::Exception::
getCode() const
{
  return _code;
}
