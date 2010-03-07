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

namespace {
  void insertAsIterations(int amount, const sk::util::String& data) {
    struct Director : public sk::oci::abstract::Director {
      Director(int amount, const sk::util::String& data)
        : _amount(amount), _data(data), _counter(0) {}

      void prepareStatement(sk::oci::Statement& statement) const {
        if(_counter == 0) {
          statement.bindIntTag(":id");
          statement.bindCharsTag(":name", 40);
        }
        statement.boundMutableData(0).setIntValue(++_counter);
        statement.boundMutableData(1).setCharsValue(_data * _counter);
      }

      bool nextIteration() const {
        return _counter < _amount;
      }

      const int _amount;
      const sk::util::String& _data;
      mutable int _counter;
    };
    accessor().execute("insert into " + testTable() + " values (:id, :name)", Director(amount, data));
  }

  void insertAsArray(int amount, const sk::util::String& data) {
    struct Director : public sk::oci::abstract::Director {
      Director(int amount, const sk::util::String& data)
        : _amount(amount), _data(data) {}

      void prepareStatement(sk::oci::Statement& statement) const {
        statement.setCapacity(_amount);

        sk::util::Integers ids;
        sk::util::Strings names;

        for(int counter=1; counter <= _amount; ++counter) {
          ids << counter;
          names << _data * counter;
        }
        statement.bindIntTag(":id", ids);
        statement.bindCharsTag(":name", 40, names);
      }

      const int _amount;
      const sk::util::String& _data;
    };
    accessor().execute("insert into " + testTable() + " values (:id, :name)", Director(amount, data));
  }

  void selectAll(sk::util::Strings& depot) {
    struct Director : public sk::oci::abstract::Director {
      Director(sk::util::Strings& depot) 
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
    accessor().execute("select * from " + testTable(), Director(depot));
  }
}

void
InsertSelectTest::
testInsertAsIterations()
{
  insertAsIterations(5, "a");

  sk::util::Strings depot;
  selectAll(depot);

  CPPUNIT_ASSERT_EQUAL(5, depot.size());

  CPPUNIT_ASSERT_EQUAL("1:a", depot.get(0));
  CPPUNIT_ASSERT_EQUAL("2:aa", depot.get(1));
  CPPUNIT_ASSERT_EQUAL("3:aaa", depot.get(2));
  CPPUNIT_ASSERT_EQUAL("4:aaaa", depot.get(3));
  CPPUNIT_ASSERT_EQUAL("5:aaaaa", depot.get(4));
}

void
InsertSelectTest::
testInsertAsArray()
{
  insertAsArray(3, "b");

  sk::util::Strings depot;
  selectAll(depot);

  CPPUNIT_ASSERT_EQUAL(3, depot.size());

  CPPUNIT_ASSERT_EQUAL("1:b", depot.get(0));
  CPPUNIT_ASSERT_EQUAL("2:bb", depot.get(1));
  CPPUNIT_ASSERT_EQUAL("3:bbb", depot.get(2));
}
