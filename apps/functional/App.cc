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

#include "App.h"

static const sk::util::String __className("test::App");

test::App::
App(const sk::util::String& config)
{
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

void
test::App::
setup()
{
}
