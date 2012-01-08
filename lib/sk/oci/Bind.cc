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
#include <sk/util/processor/Aliasing.hxx>

#include <sk/oci/Bind.h>
#include <sk/oci/bind/in.h>
#include <sk/oci/bind/out.h>

static const sk::util::String __className("sk::oci::Bind");

sk::oci::Bind::
Bind()
  : _scope(*this)
{
}

sk::oci::Bind::
Bind(const sk::oci::Bind& other)
  : _scope(other._scope)
{
  other._binds.forEach(sk::util::processor::Aliasing<const sk::oci::Bind, sk::oci::Bind>(_binds));
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

const sk::rt::Scope&
sk::oci::Bind::
getScope() const
{
  return _scope;
}

void
sk::oci::Bind::
accept(sk::oci::Statement& statement) const
{
  _scope.notice(SK_METHOD) << "Accepting statement, binds=" << _binds.inspect();

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
  _scope.notice(SK_METHOD) << "Accepting cursor, binds=" << _binds.inspect();

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
}

void
sk::oci::Bind::
processCursor(sk::oci::Cursor& cursor, sk::oci::bind::Data& data) const
{
}

sk::oci::Bind&
sk::oci::Bind::
operator<<(const sk::oci::Bind& other)
{
  _binds.add(other);

  _scope.notice(SK_METHOD) << "Added generic bind: " << _binds.inspect();
  return *this;
}

sk::oci::bind::in
sk::oci::Bind::
operator<<(const sk::oci::bind::in& other)
{
  _scope.notice(SK_METHOD) << "Adding in bind";

  sk::oci::bind::in item(other);
  item << *this;
  return item;
}

sk::oci::bind::out
sk::oci::Bind::
operator<<(const sk::oci::bind::out& other)
{
  _scope.notice(SK_METHOD) << "Adding out bind";

  sk::oci::bind::out item(other);
  item << *this;
  return item;
}
