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

#include <sk/oci/BindSizeException.h>

static const sk::util::String __className("sk::oci::BindSizeException");

sk::oci::BindSizeException::
BindSizeException(const sk::util::String& origin, uint32_t expected, uint32_t actual)
  : sk::oci::Exception(origin, "Wrong number of bind values: need " + sk::util::String::valueOf(expected) + ", got " + sk::util::String::valueOf(actual)),
    _expected(expected), _actual(actual)
{
}

const sk::util::Class
sk::oci::BindSizeException::
getClass() const
{
  return sk::util::Class(__className);
}

uint32_t
sk::oci::BindSizeException::
getExpected() const
{
  return _expected;
}

uint32_t
sk::oci::BindSizeException::
getActual() const
{
  return _actual;
}
