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

#include "Cursor.h"

static const sk::util::String __className("sk::oci::db::Cursor");

sk::oci::db::Cursor::
Cursor(db::Statement& statement)
  : _statement(statement) 
{
}

sk::oci::db::Cursor::
~Cursor()
{
}

const sk::util::Class
sk::oci::db::Cursor::
getClass() const
{
  return sk::util::Class(__className);
}

uint64_t 
sk::oci::db::Cursor::
rowCount()
{
  return _statement.rowCount();
}

void 
sk::oci::db::Cursor::
forEachColumn(const sk::util::Processor<const info::Column>& processor)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}
