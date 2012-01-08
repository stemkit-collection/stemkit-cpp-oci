/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/oci/LogonException.h>

static const sk::util::String __className("sk::oci::LogonException");

sk::oci::LogonException::
LogonException(const sk::util::String& connectString, const sk::util::String& message)
  : sk::oci::Exception(connectString, message)
{
}

const sk::util::Class
sk::oci::LogonException::
getClass() const
{
  return sk::util::Class(__className);
}
