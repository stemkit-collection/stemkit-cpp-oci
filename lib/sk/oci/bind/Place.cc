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
#include <sk/util/Holder.cxx>

#include "Place.h"

static const sk::util::String __className("sk::oci::bind::Place");

sk::oci::bind::Place::
Place()
{
}

sk::oci::bind::Place::
~Place()
{
}

const sk::util::Class
sk::oci::bind::Place::
getClass() const
{
  return sk::util::Class(__className);
}

void
sk::oci::bind::Place::
setValue(sk::oci::Value* value)
{
  _valueHolder.set(value);
}

const sk::oci::Value&
sk::oci::bind::Place::
getValue() const
{
  return _valueHolder.get();
}
