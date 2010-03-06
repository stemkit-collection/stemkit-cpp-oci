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

const test::App&
test::App::
get() 
{
  return _appHolder.get();
}


void
test::App::
setup()
{
}
