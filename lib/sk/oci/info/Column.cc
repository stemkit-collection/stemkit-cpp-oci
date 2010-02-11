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
#include <sk/util/StringArray.h>

#include <sk/oci/info/Column.h>

static const sk::util::String __className("sk::oci::info::Column");

sk::oci::info::Column::
Column(const sk::util::String& name, const info::Type& type, uint32_t size)
  : _name(name), _type(type), _size(size)
{
}

sk::oci::info::Column::
~Column()
{
}

const sk::util::Class
sk::oci::info::Column::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::util::String
sk::oci::info::Column::
inspect() const
{
  sk::util::StringArray depot;

  depot << "name=" + _name.inspect();
  depot << "type=" + _type.inspect();

  if(_objectName.isEmpty() == false) {
    depot << "object=" + _schemaName.inspect() + '.' + _objectName.inspect();
  }
  depot << "size=" + sk::util::String::valueOf(_size);

  return "<Column: " + depot.join(", ") + ">";
}

void
sk::oci::info::Column::
setSchemaName(const sk::util::String& name)
{
  _schemaName = name;
}

void
sk::oci::info::Column::
setObjectName(const sk::util::String& name)
{
  _objectName = name;
}
