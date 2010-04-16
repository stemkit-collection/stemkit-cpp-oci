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

#include <sk/oci/bind/Data.h>

static const sk::util::String __className("sk::oci::bind::Data");

sk::oci::bind::Data::
Data()
{
}

sk::oci::bind::Data::
~Data()
{
}

const sk::util::Class
sk::oci::bind::Data::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String& 
sk::oci::bind::Data::
string(int position) const
{
  return strings(position).get(0);
}

uint32_t 
sk::oci::bind::Data::
integer(int position) const
{
  return integers(position).get(0);
}

const sk::util::Integers& 
sk::oci::bind::Data::
integers(int position) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::util::Strings& 
sk::oci::bind::Data::
strings(int position) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
