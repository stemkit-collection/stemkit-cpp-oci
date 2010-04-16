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
#include <sk/util/Holder.cxx>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/StreamLiner.h>

#include <sk/oci/db/Accessor.h>
#include <sk/oci/LogonException.h>
#include <sk/oci/ConnectionStateException.h>
#include <sk/oci/abstract/Director.h>
#include <sk/oci/Data.h>
#include <sk/oci/info/Column.h>

#include <oci.h>
#include "Environment.h"
#include "handle/Error.h"
#include "handle/Server.h"
#include "handle/Session.h"
#include "handle/Service.h"

#include "Statement.h"
#include "Cursor.h"
#include "BindingDirector.h"

#include <iostream>

struct sk::oci::db::Accessor::Data : public virtual sk::util::Object {
  Data()
    : error(env), server(env, error), session(env, error), service(error, session, server) {}

  db::Environment env;
  db::handle::Error error;
  db::handle::Session session;
  db::handle::Server server;
  db::handle::Service service;
};

static const sk::util::String __className("sk::oci::db::Accessor");

sk::oci::db::Accessor::
Accessor(const sk::util::String& username, const sk::util::String& password, const sk::util::String& database)
  : _username(username), _password(password), _database(database), _connected(false),
    _scope(__className), _dataHolder(new Data), _data(_dataHolder.getMutable())
{
  logon();
}

sk::oci::db::Accessor::
~Accessor()
{
  logoff();
}

const sk::util::Class
sk::oci::db::Accessor::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::oci::db::Accessor::
logon()
{
  if(_connected == true) {
    throw sk::oci::ConnectionStateException(getConnectString(), "Already connected");
  }
  try {
    _data.env.init(OCI_OBJECT | OCI_THREADED);
    _data.error.init();
    _data.session.init(_username, _password);
    _data.server.init(_database);
    _data.service.init();

    _connected = true;
  }
  catch(const sk::util::Exception& exception) {
    logoff();
    throw sk::oci::LogonException(getConnectString(), exception.getMessage());
  }
  catch(const std::exception& exception) {
    logoff();
    throw sk::oci::LogonException(getConnectString(), exception.what());
  }
}

const sk::util::String
sk::oci::db::Accessor::
getConnectString() const
{
  return _username + '/' + _password + '@' + _database;
}

void 
sk::oci::db::Accessor::
logoff()
{
  sk::util::Exception::guard(sk::util::StreamLiner(std::cerr), _data.service, &db::handle::Service::reset);
  sk::util::Exception::guard(sk::util::StreamLiner(std::cerr), _data.server, &db::handle::Server::reset);
  sk::util::Exception::guard(sk::util::StreamLiner(std::cerr), _data.session, &db::handle::Session::reset);
  sk::util::Exception::guard(sk::util::StreamLiner(std::cerr), _data.error, &db::handle::Error::reset);
  sk::util::Exception::guard(sk::util::StreamLiner(std::cerr), _data.env, &db::Environment::reset);

  _connected = false;
}

void 
sk::oci::db::Accessor::
close()
{
  logoff();
}

namespace {
  inline void ensureConnected(bool state, const char* origin) {
    if(state == false) {
      throw sk::oci::ConnectionStateException(origin, "Not connected");
    }
  }
}

void 
sk::oci::db::Accessor::
commit()
{
  ensureConnected(_connected, __FUNCTION__);
  _data.service.commit();
}

void 
sk::oci::db::Accessor::
rollback()
{
  ensureConnected(_connected, __FUNCTION__);
  _data.service.rollback();
}

uint32_t 
sk::oci::db::Accessor::
execute(const sk::util::String& sql)
{
  return execute(sql, sk::oci::abstract::Director());
}

uint32_t 
sk::oci::db::Accessor::
execute(const sk::util::String& sql, const sk::oci::Director& director)
{
  ensureConnected(_connected, __FUNCTION__);
  db::Statement statement(_data.error, sql);

  do {
    director.prepareStatement(statement);
    statement.execute(_data.service);
  }
  while(director.nextIteration() == true);

  db::Cursor cursor(statement);
  director.processCursor(cursor);

  return cursor.rowCount();
}

const sk::oci::bind::Data
sk::oci::db::Accessor::
execute(const sk::util::String& sql, const sk::oci::Bind& bind)
{
  sk::rt::Scope scope = _scope.scope(__FUNCTION__);
  db::BindingDirector director(bind);
  execute(sql, director);

  return director.data();
}

namespace {
  struct TableDescriber : public sk::oci::abstract::Director, public virtual sk::util::Processor<const sk::oci::info::Column> {
    TableDescriber(sk::oci::info::Table& table)
      : _table(table) {}

    void prepareStatement(sk::oci::Statement& statement) const {
      statement.setDescribeOnly(true);
    }

    void processCursor(sk::oci::Cursor& cursor) const {
      cursor.forEachColumn(*this);
    }

    void process(const sk::oci::info::Column& column) const {
      _table.add(column);
    }

    sk::oci::info::Table& _table;
  };
}

const sk::oci::info::Table 
sk::oci::db::Accessor::
describeTable(const sk::util::String& name)
{
  ensureConnected(_connected, __FUNCTION__);
  info::Table table(name);
  execute("select * from " + name, TableDescriber(table));

  return table;
}

namespace {
  struct CountingDirector : public sk::oci::abstract::Director {
    CountingDirector(uint32_t& counter) 
      : _counter(counter) {}

    void processCursor(sk::oci::Cursor& cursor) const {
      int index = cursor.bindIntAt(1);
      cursor.fetch();

      _counter = cursor.boundData(index).intValue();
    }

    uint32_t& _counter;
  };
}

uint32_t
sk::oci::db::Accessor::
tableSize(const sk::util::String& name)
{
  uint32_t counter = 0;

  ensureConnected(_connected, __FUNCTION__);
  execute("select count(*) from " + name, CountingDirector(counter));

  return counter;
}
