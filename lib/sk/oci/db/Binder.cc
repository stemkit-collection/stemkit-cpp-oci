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

#include "Binder.h"
#include "data/String.h"
#include "data/Integer.h"

static const sk::util::String __className("sk::oci::db::Binder");

sk::oci::db::Binder::
Binder()
{
}

sk::oci::db::Binder::
~Binder()
{
}

const sk::util::Class
sk::oci::db::Binder::
getClass() const
{
  return sk::util::Class(__className);
}
