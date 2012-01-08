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

#include "PositionalPlace.h"

static const sk::util::String __className("sk::oci::bind::PositionalPlace");

sk::oci::bind::PositionalPlace::
PositionalPlace(int position)
  : _position(position)
{
}

sk::oci::bind::PositionalPlace::
~PositionalPlace()
{
}

const sk::util::Class
sk::oci::bind::PositionalPlace::
getClass() const
{
  return sk::util::Class(__className);
}

void
sk::oci::bind::PositionalPlace::
bind(sk::oci::Statement& statement) const
{
  getValue().bindPosition(_position, statement);
}
