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
#include <sk/util/Strings.h>

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
  sk::util::Strings depot;

  depot << "name=" + _name.inspect();
  depot << "type=" + _type.inspect();

  if(_typeName.isEmpty() == false) {
    depot << "object=" + _typeName;
  }
  depot << "size=" + sk::util::String::valueOf(_size);

  return "<Column: " + depot.join(", ") + ">";
}

void
sk::oci::info::Column::
setTypeName(const sk::util::String& schema, const sk::util::String& object)
{
  _typeName = schema + '.' + object;
}

const sk::util::String
sk::oci::info::Column::
getName() const
{
  return _name;
}

const sk::oci::info::Type&
sk::oci::info::Column::
getType() const
{
  return _type;
}

int
sk::oci::info::Column::
getSize() const
{
  return _size;
}

const sk::util::String
sk::oci::info::Column::
getTypeName() const
{
  return _typeName;
}
