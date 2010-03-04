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
#include <sk/oci/Data.h>

#include <sk/rt/Scope.h>
#include <sk/rt/config/InlineLocator.h>
#include <sk/util/Pathname.h>

#include <iostream>
#include <iomanip>

void printContent(sk::oci::Accessor& accessor, const sk::util::String& table);

int main(int argc, const char* const argv[])
{
  sk::rt::Scope::controller().loadXmlConfig(
    sk::rt::config::InlineLocator(
      "<scope>\n"
      "  <log level='info' show-time='true' />\n"
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

namespace {
  struct ContentPrinter : public sk::oci::abstract::Director {
    void prepareStatement(sk::oci::Statement& statement) const {
      statement.bindIntTag(":upper", 9);
      statement.bindCharsTag(":lower", 2, "2");
    }

    void processCursor(sk::oci::Cursor& cursor) const {
      cursor.useColumnCodes(true);
      cursor.useTruncate(true);

      const sk::oci::info::Column c1 = cursor.columnAt(0);
      const sk::oci::info::Column c2 = cursor.columnAt(1);

      const sk::oci::Data& d1 = cursor.boundData(cursor.bindIntAt(1));
      const sk::oci::Data& d2 = cursor.boundData(cursor.bindCharsAt(2, c2.getSize()));

      while(cursor.fetch() != 0) {
        std::cout 
          << c1.getName() << "=" << d1.info() << ", "
          << c2.getName() << "=" << d2.info()
          << std::endl
        ;
      }
      std::cerr << "Processed " << cursor.rowCount() << " row(s)" << std::endl;
    }
  };
}

void printContent(sk::oci::Accessor& accessor, const sk::util::String& table) {
  accessor.execute("select * from " + table + " where c1 >= :lower and c1 < :upper", ContentPrinter());
}
