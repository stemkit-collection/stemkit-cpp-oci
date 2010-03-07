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
#include <sk/oci/Data.h>

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
      statement.setCapacity(5);
    }
  };
  accessor().execute("insert into " + testTable() + " values (3, 'uuu')", Director());
  CPPUNIT_ASSERT_EQUAL(uint64_t(7), accessor().tableSize(testTable()));
}

void
InsertSelectTest::
testInsertSelect()
{
  struct InsertingDirector : public sk::oci::abstract::Director {
    InsertingDirector(int iterations)
      : _iterations(iterations), _counter(0) {}

    void prepareStatement(sk::oci::Statement& statement) const {
      if(_counter == 0) {
        statement.bindIntTag(":num");
        statement.bindCharsTag(":str", 40);
      }
      statement.boundMutableData(0).setIntValue(++_counter);
      statement.boundMutableData(1).setCharsValue(sk::util::String("a") * _counter);
    }

    bool nextIteration() const {
      return _counter < _iterations;
    }

    mutable int _counter;
    const int _iterations;
  };
  accessor().execute("insert into " + testTable() + " values (:num, :str)", InsertingDirector(5));

  sk::util::Strings depot;
  struct SelectingDirector : public sk::oci::abstract::Director {
    SelectingDirector(sk::util::Strings& depot) 
      : _depot(depot) {}

    void processCursor(sk::oci::Cursor& cursor) const {
      const sk::oci::Data& num = cursor.boundData(cursor.bindIntAt(1));
      const sk::oci::Data& str = cursor.boundData(cursor.bindCharsAt(2, 40));

      while(cursor.fetch() != 0) {
        _depot << sk::util::String::valueOf(num.intValue()) + ':' + str.stringValue();
      }
    }
    sk::util::Strings& _depot;
  };
  accessor().execute("select * from " + testTable(), SelectingDirector(depot));

  CPPUNIT_ASSERT_EQUAL(5, depot.size());
  CPPUNIT_ASSERT_EQUAL("1:a", depot.get(0));
  CPPUNIT_ASSERT_EQUAL("2:aa", depot.get(1));
  CPPUNIT_ASSERT_EQUAL("3:aaa", depot.get(2));
  CPPUNIT_ASSERT_EQUAL("4:aaaa", depot.get(3));
  CPPUNIT_ASSERT_EQUAL("5:aaaaa", depot.get(4));
}
