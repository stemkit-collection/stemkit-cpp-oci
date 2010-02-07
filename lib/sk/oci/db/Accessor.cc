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

static const sk::util::String __className("sk::oci::db::Accessor");

struct sk::oci::db::Accessor::Data : public virtual sk::util::Object {
};

sk::oci::db::Accessor::
Accessor(const sk::util::String& username, const sk::util::String& password, const sk::util::String& database)
  : _username(username), _password(password), _database(database),
    _dataHolder(new Data), _data(_dataHolder.get())
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
  throw sk::util::UnsupportedOperationException(SK_METHOD);
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

