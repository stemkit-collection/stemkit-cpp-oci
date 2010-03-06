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
#include <sk/util/Holder.cxx>
#include <sk/oci/db/Accessor.h>

#include "App.h"

static const sk::util::String __className("test::App");
sk::util::Holder<test::App> test::App::_appHolder;

test::App::
App()
  : _scope(__className)
{
  if(_appHolder.isEmpty() == false) {
    throw sk::util::IllegalStateException("Only one app instance is allowed");
  }
  _appHolder.set(*this);
}

test::App::
~App()
{
}

const sk::util::Class
test::App::
getClass() const
{
  return sk::util::Class(__className);
}

app::Fixture& 
test::App::
fixture() 
{
  return _appHolder.getMutable();
}


void
test::App::
setup()
{
  _accessorHolder.set(new sk::oci::db::Accessor(user(), password(), sid()));
}

const sk::util::String
test::App::
user() const
{
  const sk::util::String name = sid();
  try {
    return _scope.getProperty("user");
  }
  catch(const sk::util::MissingResourceException& exception) {
    throw sk::util::IllegalStateException("User name for accessing sid " + name.inspect() + " not configured");
  }
}

const sk::util::String
test::App::
password() const
{
  const sk::util::String username = user();
  try {
    return _scope.getProperty("password");
  }
  catch(const sk::util::MissingResourceException& exception) {
    throw sk::util::IllegalStateException("Password for user " + username.inspect() + " not configured");
  }
}

const sk::util::String
test::App::
sid() const
{
  try {
    return _scope.getProperty("sid");
  }
  catch(const sk::util::MissingResourceException& exception) {
    throw sk::util::IllegalStateException("Database SID not configured");
  }
}

sk::oci::Accessor&
test::App::
dbAccessor()
{
  return _accessorHolder.getMutable();
}
