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

#include <sk/oci/NoDataException.h>

static const sk::util::String __className("sk::oci::NoDataException");

sk::oci::NoDataException::
NoDataException(const sk::util::String& origin)
  : sk::oci::Exception(origin, "No data")
{
}

const sk::util::Class
sk::oci::NoDataException::
getClass() const
{
  return sk::util::Class(__className);
}
