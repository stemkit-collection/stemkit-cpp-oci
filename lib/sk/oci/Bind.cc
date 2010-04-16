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
#include <sk/util/ArrayList.cxx>

#include <sk/oci/Bind.h>

static const sk::util::String __className("sk::oci::Bind");

sk::oci::Bind::
Bind()
{
}

sk::oci::Bind::
~Bind()
{
}

const sk::util::Class
sk::oci::Bind::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::oci::Bind::
accept(sk::oci::Statement& statement) const
{
  struct Acceptor : public virtual sk::util::Processor<const sk::oci::Bind> {
    Acceptor(sk::oci::Statement& statement) 
      : _statement(statement) {}

    void process(const sk::oci::Bind& bind) const {
      bind.accept(_statement);
    }
    sk::oci::Statement& _statement;
  };
  _binds.forEach(Acceptor(statement));
  prepareStatement(statement);
}

void 
sk::oci::Bind::
accept(sk::oci::Cursor& cursor, sk::oci::bind::Data& data) const
{
  struct Acceptor : public virtual sk::util::Processor<const sk::oci::Bind> {
    Acceptor(sk::oci::Cursor& cursor, sk::oci::bind::Data& data) 
      : _cursor(cursor), _data(data) {}

    void process(const sk::oci::Bind& bind) const {
      bind.accept(_cursor, _data);
    }
    sk::oci::Cursor& _cursor;
    sk::oci::bind::Data& _data;
  };
  _binds.forEach(Acceptor(cursor, data));
  processCursor(cursor, data);
}

void 
sk::oci::Bind::
prepareStatement(sk::oci::Statement& statement) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::oci::Bind::
processCursor(sk::oci::Cursor& cursor, sk::oci::bind::Data& data) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

sk::oci::Bind& 
sk::oci::Bind::
operator<<(const sk::oci::Bind& other)
{
  _binds.add(other);
  return *this;
}
