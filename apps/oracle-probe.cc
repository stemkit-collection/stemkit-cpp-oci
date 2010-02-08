/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/oci/db/Accessor.h>
#include <sk/rt/Scope.h>

int main(int argc, const char* const argv[])
{
  sk::rt::Scope scope("main");

  try {
    sk::oci::db::Accessor accessor("aaa", "bbb", "ccc");
    accessor.close();
  }
  catch(const std::exception& exception) {
    scope.error("EX") << exception.what();
    return 2;
  }
  return 0;
}
