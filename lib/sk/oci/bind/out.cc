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
#include <sk/util/UnsupportedOperationException.h>

#include <sk/oci/bind/out.h>

static const sk::util::String __className("sk::oci::bind::out");

sk::oci::bind::out::
out()
  : _amount(1), _skip(0)
{
}

sk::oci::bind::out::
out(uint32_t amount)
  : _amount(amount), _skip(0)
{
}

sk::oci::bind::out::
out(uint32_t amount, uint32_t skip)
  : _amount(amount), _skip(skip)
{
}

sk::oci::bind::out::
~out()
{
}

const sk::util::Class
sk::oci::bind::out::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::oci::bind::out::
prepareStatement(sk::oci::Statement& statement) const
{
}

void 
sk::oci::bind::out::
processCursor(sk::oci::Cursor& cursor, sk::oci::bind::Data& data) const
{
  getScope().notice(SK_METHOD) << "in";
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::oci::bind::out& 
sk::oci::bind::out::
operator<<(const sk::oci::Integers& values)
{
  getScope().notice(SK_METHOD) << "Integers";
  return *this;
}

sk::oci::bind::out& 
sk::oci::bind::out::
operator<<(const sk::oci::Strings& values)
{
  getScope().notice(SK_METHOD) << "Strings";
  return *this;
}

