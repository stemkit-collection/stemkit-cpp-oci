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
#include <sk/oci/info/Type.h>

sk::oci::info::Type::container_t sk::oci::info::Type::_types;
int sk::oci::info::Type::_counter = 0;

#define DEFINE_TYPE(type) const sk::oci::info::Type sk::oci::info::Type::SK_##type(#type) 

DEFINE_TYPE(UNKNOWN);
DEFINE_TYPE(NUMBER);
DEFINE_TYPE(VARCHAR2);
DEFINE_TYPE(VARCHAR);
DEFINE_TYPE(CHAR);
DEFINE_TYPE(REF);
DEFINE_TYPE(DATE);
DEFINE_TYPE(REAL);
DEFINE_TYPE(DOUBLE);
DEFINE_TYPE(FLOAT);
DEFINE_TYPE(DECIMAL);
DEFINE_TYPE(OCTET);
DEFINE_TYPE(INTEGER);
DEFINE_TYPE(SMALLINT);
DEFINE_TYPE(RAW);
DEFINE_TYPE(VARRAY);
DEFINE_TYPE(TABLE);
DEFINE_TYPE(CLOB);
DEFINE_TYPE(BLOB);
DEFINE_TYPE(BFILE);
DEFINE_TYPE(OBJECT);
DEFINE_TYPE(NAMEDCOLLECTION);

static const sk::util::String __className("sk::oci::info::Type");

sk::oci::info::Type::
Type(const sk::util::String& name)
  : _name(name), _value(++_counter)
{
  _types.push_back(this);
}

sk::oci::info::Type::
~Type()
{
  _types.pop_back();
  --_counter;
}

const sk::util::Class
sk::oci::info::Type::
getClass() const
{
  return sk::util::Class(__className);
}

bool
sk::oci::info::Type::
operator == (const info::Type& other) 
{
  return _value == other.toInt();
}

const sk::util::String
sk::oci::info::Type::
getName() const
{
  return _name;
}

int
sk::oci::info::Type::
toInt() const
{
  return _value;
}

const sk::util::String
sk::oci::info::Type::
toString() const
{
  return getName();
}

const sk::oci::info::Type&
sk::oci::info::Type::
valueOf(const sk::util::String& name)
{
  for(container_t::iterator iterator = _types.begin(); iterator != _types.end(); ++iterator) {
    if(name.equalsIgnoreCase((*iterator)->getName())) {
      return *(*iterator);
    }
  }
  return SK_UNKNOWN;
}

const sk::oci::info::Type&
sk::oci::info::Type::
valueOf(int value)
{
  for(container_t::iterator iterator = _types.begin(); iterator != _types.end(); ++iterator) {
    if(value == (*iterator)->toInt()) {
      return *(*iterator);
    }
  }
  return SK_UNKNOWN;
}
