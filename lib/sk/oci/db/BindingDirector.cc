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
#include <sk/util/UnsupportedOperationException.h>

#include "BindingDirector.h"

static const sk::util::String __className("sk::oci::db::BindingDirector");

sk::oci::db::BindingDirector::
BindingDirector(const sk::oci::Bind& bind)
  : _bind(bind)
{
}

sk::oci::db::BindingDirector::
~BindingDirector()
{
}

const sk::util::Class
sk::oci::db::BindingDirector::
getClass() const
{
  return sk::util::Class(__className);
}


void 
sk::oci::db::BindingDirector::
prepareStatement(sk::oci::Statement& statement) const
{
  _bind.accept(statement);
}

void 
sk::oci::db::BindingDirector::
processCursor(sk::oci::Cursor& cursor) const
{
  _bind.accept(cursor, _data);
}

bool 
sk::oci::db::BindingDirector::
nextIteration() const
{
  return false;
}

const sk::oci::bind::Data&
sk::oci::db::BindingDirector::
data() const
{
  return _data;
}
