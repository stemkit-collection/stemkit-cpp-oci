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
#include <sk/oci/Cursor.h>

#include "TableDescriber.h"

static const sk::util::String __className("sk::oci::db::TableDescriber");

sk::oci::db::TableDescriber::
TableDescriber(info::Table& table)
  : _table(table)
{
}

sk::oci::db::TableDescriber::
~TableDescriber()
{
}

const sk::util::Class
sk::oci::db::TableDescriber::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::oci::db::TableDescriber::
prepareStatement(sk::oci::Statement& statement) const
{
  statement.setDescribeOnly(true);
}

void 
sk::oci::db::TableDescriber::
processCursor(sk::oci::Cursor& cursor) const
{
  cursor.forEachColumn(*this);
}

void
sk::oci::db::TableDescriber::
process(const info::Column& column) const 
{
  _table.add(column);
}
