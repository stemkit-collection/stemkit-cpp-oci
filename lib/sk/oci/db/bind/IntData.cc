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

#include "IntData.h"

static const sk::util::String __className("sk::oci::db::bind::IntData");

sk::oci::db::bind::IntData::
IntData(uint32_t position, uint32_t value)
  : bind::Data(position, SQLT_INT, sizeof(value))
{
  intValue() = value;
}

const sk::util::Class
sk::oci::db::bind::IntData::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String
sk::oci::db::bind::IntData::
inspect() const
{
  return bind::Data::inspect();
}
