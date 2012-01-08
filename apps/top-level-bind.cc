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
#include <sk/rt/config/InlineLocator.h>
#include <sk/util/Pathname.h>
#include <sk/oci/bind/in.h>
#include <sk/oci/bind/out.h>
#include <sk/oci/Integers.h>
#include <sk/oci/Strings.h>

#include <iostream>
#include <iomanip>

void printContent(sk::oci::Accessor& accessor, const sk::util::String& table);

int main(int argc, const char* const argv[])
{
  sk::rt::Scope::controller().loadXmlConfig(
    sk::rt::config::InlineLocator(
      "<scope>\n"
      "  <log level='info' show-time='true' show-object='false'/>\n"
      "</scope>\n"
    )
  );

  sk::util::Pathname program(argv[0]);
  sk::rt::Scope scope("main");

  try {
    if(argc != 2) {
      throw sk::util::Exception("USAGE: " + program.basename() + " <table>");
    }
    sk::oci::db::Accessor accessor("gfb", "gfb", "w102a32f.alvspxl09.quest.com");
    scope.info() << "Connected to " << accessor.getConnectString().inspect();

    printContent(accessor, argv[1]);
  }
  catch(const sk::util::Exception& exception) {
    scope.error("EX") << exception.getMessage();
    return 2;
  }
  catch(const std::exception& exception) {
    scope.error("EX") << exception.what();
    return 2;
  }
  return 0;
}

void printContent(sk::oci::Accessor& accessor, const sk::util::String& table) {
  sk::rt::Scope scope(__FUNCTION__);

  const sk::oci::bind::Data result = accessor.execute(
    "select * from where name = :name and id = :id and zip = :3" + table,
    sk::oci::Bind()
      << sk::oci::bind::in()
        << ":id" << (sk::oci::Integers() << 1 << 2 << 3)
        << ":name" << (sk::oci::Strings() << "aaa" << "bbb" << "ccc")
        << 3 << (sk::oci::Integers() << 11111 << 22222 << 33333)
      << sk::oci::bind::out(25)
        << sk::oci::Integers()
        << sk::oci::Strings(30)
  );
  scope.info() << result.integers(1);
  scope.info() << result.strings(2);
}
