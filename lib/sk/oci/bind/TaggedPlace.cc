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

#include "TaggedPlace.h"

static const sk::util::String __className("sk::oci::bind::TaggedPlace");

sk::oci::bind::TaggedPlace::
TaggedPlace(const sk::util::String& tag)
  : _tag(tag)
{
}

sk::oci::bind::TaggedPlace::
~TaggedPlace()
{
}

const sk::util::Class
sk::oci::bind::TaggedPlace::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::oci::bind::TaggedPlace::
bind(sk::oci::Statement& statement) const
{
  getValue().bindTag(_tag, statement);
}
