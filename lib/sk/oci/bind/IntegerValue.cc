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
#include <sk/oci/Statement.h>

#include "IntegerValue.h"

static const sk::util::String __className("sk::oci::bind::IntegerValue");

sk::oci::bind::IntegerValue::
IntegerValue(const sk::util::Integers& data)
  : _data(data)
{
}

sk::oci::bind::IntegerValue::
~IntegerValue()
{
}

const sk::util::Class
sk::oci::bind::IntegerValue::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::oci::bind::IntegerValue::
bindTag(const sk::util::String& tag, sk::oci::Statement& statement) const
{
  statement.bindIntTag(tag, _data);
}
