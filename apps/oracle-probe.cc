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
#include <sk/oci/abstract/Director.h>
#include <sk/rt/Scope.h>
#include <sk/rt/config/InlineLocator.h>

namespace {
  struct Director : public virtual sk::oci::abstract::Director {
    void prepareStatement(sk::oci::Statement& statement) const {
      statement.setDescribeOnly(true);
    }

    void processCursor(sk::oci::Cursor& cursor) const {
    }
  };
}

int main(int argc, const char* const argv[])
{
  sk::rt::Scope::controller().loadXmlConfig(
    sk::rt::config::InlineLocator(
      "<scope>\n"
      "  <log level='info' show-time='true' />\n"
      "</scope>\n"
    )
  );

  sk::rt::Scope scope("main");

  try {
    sk::oci::db::Accessor accessor("gfb", "gfb", "w102a32f.alvspxl09.quest.com");
    scope.info() << "Connected to " << accessor.getConnectString().inspect();

    scope.info("select") << accessor.execute("select * from just_table");
    scope.info("select with director") << accessor.execute("select * from just_table", Director());

    accessor.close();
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
