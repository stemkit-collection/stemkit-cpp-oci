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

#include <iostream>
#include <iomanip>

void printContent(sk::oci::Accessor& accessor, const sk::util::String& table);

int main(int argc, const char* const argv[])
{
  sk::oci::db::Accessor accessor("gfb", "gfb", "w102a32f.alvspxl09.quest.com");
  std::cerr << "Connected to " << accessor.getConnectString().inspect() << std::endl;

  printContent(accessor, argv[1]);
  return 0;
}

namespace {
  struct ContentPrinter : public sk::oci::abstract::Director {
    void processCursor(sk::oci::Cursor& cursor) const {
      cursor.useTruncate(true);
      cursor.useColumnCodes(true);
      
      const sk::oci::info::Column c1 = cursor.columnAt(0);
      const sk::oci::info::Column c2 = cursor.columnAt(1);

      int p1 = cursor.bindIntAt(1);
      int p2 = cursor.bindStringAt(2, c2.getSize());

      const sk::oci::Data& d1 = cursor.boundDataAt(p1);
      const sk::oci::Data& d2 = cursor.boundDataAt(p2);

      while(cursor.fetch() != 0) {
        std::cout << std::boolalpha
          << c1.getName() << "=" << d1.intValue() << " (" 
            << d1.isNull() << ", " << d1.isTruncated() 
          << "), " 
          << c2.getName() << "=" << sk::util::String(d2.stringValue().getChars(), d2.getSize()).inspect() << " ("  
            << d2.isNull() << ", " << d2.isTruncated() 
          << ")"
          << std::endl
        ;
      }
      std::cerr << "Processed " << cursor.rowCount() << " row(s)" << std::endl;
    }
  };
}

void printContent(sk::oci::Accessor& accessor, const sk::util::String& table) {
  accessor.execute("select * from " + table, ContentPrinter());
}
