/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "InsertSelectTest.h"
#include "App.h"
#include <sk/oci/abstract/Director.h>
#include <sk/util/IndexOutOfBoundsException.h>

CPPUNIT_TEST_SUITE_REGISTRATION(InsertSelectTest);

InsertSelectTest::
InsertSelectTest()
{
}

InsertSelectTest::
~InsertSelectTest()
{
}

namespace {
  app::Fixture& fixture() {
    return test::App::fixture();
  }

  sk::oci::Accessor& accessor() {
    return fixture().dbAccessor();
  }

  const sk::util::String testTable() {
    return fixture().testTable();
  }
}

void
InsertSelectTest::
setUp()
{
  fixture().truncateTestTable();
}

void
InsertSelectTest::
tearDown()
{
}

void
InsertSelectTest::
testSelectList()
{
  struct Director : public sk::oci::abstract::Director {
    void processCursor(sk::oci::Cursor& cursor) const {
      CPPUNIT_ASSERT_EQUAL(2U, cursor.columnCount());
      CPPUNIT_ASSERT_EQUAL("ID", cursor.columnAt(0).getName());
      CPPUNIT_ASSERT_EQUAL("NUMBER", cursor.columnAt(0).getType().inspect());
      CPPUNIT_ASSERT_EQUAL("NAME", cursor.columnAt(1).getName());
      CPPUNIT_ASSERT_EQUAL("VARCHAR", cursor.columnAt(1).getType().inspect());
      CPPUNIT_ASSERT_EQUAL(40, cursor.columnAt(1).getSize());
      CPPUNIT_ASSERT_THROW(cursor.columnAt(2), sk::util::IndexOutOfBoundsException);
    }
  };
  accessor().execute("select * from " + testTable(), Director());
}

void 
InsertSelectTest::
testRowCountAfterInsert()
{
  CPPUNIT_ASSERT_EQUAL(uint64_t(0), accessor().tableSize(testTable()));
  accessor().execute("insert into " + testTable() + " values (1, 'abc')");
  accessor().execute("insert into " + testTable() + " values (2, 'zzz')");
  CPPUNIT_ASSERT_EQUAL(uint64_t(2), accessor().tableSize(testTable()));

  struct Director : public sk::oci::abstract::Director {
    void prepareStatement(sk::oci::Statement& statement) const {
      statement.setIterations(5);
    }
  };
  accessor().execute("insert into " + testTable() + " values (3, 'uuu')", Director());
  CPPUNIT_ASSERT_EQUAL(uint64_t(7), accessor().tableSize(testTable()));
}
