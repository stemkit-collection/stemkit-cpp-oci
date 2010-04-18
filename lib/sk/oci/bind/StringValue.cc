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
#include <sk/util/Injector.cxx>
#include <sk/util/reducer/Max.hxx>
#include <sk/util/mapper/Sizing.hxx>

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

void 
sk::oci::bind::StringValue::
bindTag(const sk::util::String& tag, sk::oci::Statement& statement) const
{
  int size = sk::util::Injector<sk::util::String, int>(_data).inject(sk::util::mapper::Sizing<sk::util::String>(), sk::util::reducer::Max<sk::util::String, int>());
  statement.bindCharsTag(tag, size, _data);
}
