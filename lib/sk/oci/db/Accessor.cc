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
#include <sk/oci/AbstractDirector.h>

#include <oci.h>
#include "Environment.h"
#include "handle/Error.h"
#include "handle/Server.h"
#include "handle/Session.h"
#include "handle/Service.h"

#include "Statement.h"
#include "Cursor.h"
#include "TableDescriber.h"

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
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::oci::db::Accessor::
rollback()
{
  ensureConnected(_connected, __FUNCTION__);
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::oci::info::Table 
sk::oci::db::Accessor::
describeTable(const sk::util::String& name)
{
  ensureConnected(_connected, __FUNCTION__);
  info::Table table(name);
  execute("select * from " + name, db::TableDescriber(table));

  return table;
}

uint64_t 
sk::oci::db::Accessor::
execute(const sk::util::String& sql)
{
  return execute(sql, AbstractDirector());
}

uint64_t 
sk::oci::db::Accessor::
execute(const sk::util::String& sql, const sk::oci::Director& director)
{
  ensureConnected(_connected, __FUNCTION__);
  db::Statement statement(_data.error, sql);

  director.prepareStatement(statement);
  statement.execute(_data.service);

  db::Cursor cursor(statement);
  director.processCursor(cursor);

  return cursor.rowCount();
}

