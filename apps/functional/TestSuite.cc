/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <sk/cppunit/TestRunner.h>
#include <sk/cppunit/SourcePath.h>
#include "App.h"

int main(int argc, const char* argv[])
{
  CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
  sk::cppunit::TestRunner runner;

  if(argc == 2) {
    sk::cppunit::SourcePath::setBase(argv[1]);
  }
  test::App app(sk::cppunit::SourcePath::make("config.yaml"));
  app.setup();

  runner.addTest(registry.makeTest());
  return !runner.run();
}
