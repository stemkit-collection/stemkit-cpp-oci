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

#include "Data.h"

static const sk::util::String __className("sk::oci::db::Data");

sk::oci::db::Data::
Data()
{
}

sk::oci::db::Data::
~Data()
{
}

const sk::util::Class
sk::oci::db::Data::
getClass() const
{
  return sk::util::Class(__className);
}
