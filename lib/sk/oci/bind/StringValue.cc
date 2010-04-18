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

#include "StringValue.h"

static const sk::util::String __className("sk::oci::bind::StringValue");

sk::oci::bind::StringValue::
StringValue(const sk::util::Strings& data)
  : _data(data)
{
}

sk::oci::bind::StringValue::
~StringValue()
{
}

const sk::util::Class
sk::oci::bind::StringValue::
getClass() const
{
  return sk::util::Class(__className);
}
