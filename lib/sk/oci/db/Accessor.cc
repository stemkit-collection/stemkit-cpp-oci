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

#include <sk/oci/db/Accessor.h>

#include <oci.h>
#include "Environment.h"
#include "handle/Error.h"
#include "handle/Server.h"
#include "handle/Session.h"
#include "handle/Service.h"

struct sk::oci::db::Accessor::Data : public virtual sk::util::Object {
  Data()
    : error(env), server(env, error), session(env, error), service(env, session, server, error) {}

  db::Environment env;
  db::handle::Error error;
  db::handle::Session session;
  db::handle::Server server;
  db::handle::Service service;
};

static const sk::util::String __className("sk::oci::db::Accessor");

sk::oci::db::Accessor::
Accessor(const sk::util::String& username, const sk::util::String& password, const sk::util::String& database)
  : _username(username), _password(password), _database(database),
    _scope(__className), _dataHolder(new Data), _data(_dataHolder.get())
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
  _data.env.init(OCI_OBJECT | OCI_THREADED);
  _data.error.init();
  _data.session.init(_username, _password);
  _data.server.init(_database);
  _data.service.init();
}

void 
sk::oci::db::Accessor::
logoff()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::oci::db::Accessor::
close()
{
  logoff();
}

void 
sk::oci::db::Accessor::
commit()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::oci::db::Accessor::
rollback()
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::oci::info::Table 
sk::oci::db::Accessor::
describe(const sk::util::String& name)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

uint64_t 
sk::oci::db::Accessor::
execute(const sk::util::String& sql)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

uint64_t 
sk::oci::db::Accessor::
execute(const sk::util::String& sql, const sk::oci::Director& director)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

