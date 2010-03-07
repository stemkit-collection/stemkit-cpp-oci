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
#include <sk/util/Strings.h>
#include <sk/util/ArrayList.cxx>

#include <sk/oci/info/Table.h>

static const sk::util::String __className("sk::oci::info::Table");

sk::oci::info::Table::
Table(const sk::util::String& name)
  : _name(name)
{
}

sk::oci::info::Table::
~Table()
{
}

const sk::util::Class
sk::oci::info::Table::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String
sk::oci::info::Table::
getName() const
{
  return _name;
}

void
sk::oci::info::Table::
add(const info::Column& column)
{
  _columns.add(new info::Column(column));
}

const sk::util::String
sk::oci::info::Table::
inspect() const
{
  sk::util::Strings depot;

  depot << "name=" + _name.inspect();
  depot << "columns=" + _columns.inspect();

  return "<Table: " + depot.join(", ") + ">";
}

int
sk::oci::info::Table::
columnCount() const
{
  return _columns.size();
}

const sk::oci::info::Column&
sk::oci::info::Table::
columnAt(int index) const
{
  return _columns.get(index);
}
