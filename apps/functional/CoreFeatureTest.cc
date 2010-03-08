/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "CoreFeatureTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(CoreFeatureTest);

#include "App.h"
#include "app/Fixture.h"
#include <sk/oci/info/Table.h>
#include <sk/oci/info/Column.h>
#include <sk/oci/abstract/Director.h>
#include <sk/util/IndexOutOfBoundsException.h>
#include <sk/oci/Data.h>

#include <sk/oci/db/Accessor.h>

CoreFeatureTest::
CoreFeatureTest()
{
}

CoreFeatureTest::
~CoreFeatureTest()
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
CoreFeatureTest::
setUp()
{
  fixture().dropTestTable();
  fixture().createTestTable("id integer, name varchar2(40)");
}

void
CoreFeatureTest::
tearDown()
{
}

void
CoreFeatureTest::
testDescribeTable()
{
  const sk::oci::info::Table table = accessor().describeTable(testTable());

  CPPUNIT_ASSERT_EQUAL(testTable(), table.getName());
  CPPUNIT_ASSERT_EQUAL(2, table.columnCount());

  CPPUNIT_ASSERT_EQUAL("ID", table.columnAt(0).getName());
  CPPUNIT_ASSERT_EQUAL("NUMBER", table.columnAt(0).getType().inspect());
  CPPUNIT_ASSERT(table.columnAt(0).getType().isNumber() == true);
  CPPUNIT_ASSERT(table.columnAt(0).getType().isVarChar() == false);
  CPPUNIT_ASSERT_EQUAL(22, table.columnAt(0).getSize());

  CPPUNIT_ASSERT_EQUAL("NAME", table.columnAt(1).getName());
  CPPUNIT_ASSERT_EQUAL("VARCHAR", table.columnAt(1).getType().inspect());
  CPPUNIT_ASSERT(table.columnAt(1).getType().isNumber() == false);
  CPPUNIT_ASSERT(table.columnAt(1).getType().isVarChar() == true);
  CPPUNIT_ASSERT_EQUAL(40, table.columnAt(1).getSize());
}

void
CoreFeatureTest::
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
CoreFeatureTest::
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
CoreFeatureTest::
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
CoreFeatureTest::
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

void 
CoreFeatureTest::
testRollback()
{
  CPPUNIT_ASSERT_EQUAL(uint64_t(0), accessor().tableSize(testTable()));
  insertAsArray(7, "z");
  CPPUNIT_ASSERT_EQUAL(uint64_t(7), accessor().tableSize(testTable()));

  accessor().rollback();

  CPPUNIT_ASSERT_EQUAL(uint64_t(0), accessor().tableSize(testTable()));
}

void 
CoreFeatureTest::
testRollbackAfterCommit()
{
  CPPUNIT_ASSERT_EQUAL(uint64_t(0), accessor().tableSize(testTable()));
  insertAsArray(7, "z");
  CPPUNIT_ASSERT_EQUAL(uint64_t(7), accessor().tableSize(testTable()));

  accessor().commit();
  accessor().rollback();

  CPPUNIT_ASSERT_EQUAL(uint64_t(7), accessor().tableSize(testTable()));
}

void 
CoreFeatureTest::
testCommit()
{
  CPPUNIT_ASSERT_EQUAL(uint64_t(0), accessor().tableSize(testTable()));
  insertAsArray(7, "z");
  CPPUNIT_ASSERT_EQUAL(uint64_t(7), accessor().tableSize(testTable()));

  sk::oci::db::Accessor another(fixture().user(), fixture().password(), fixture().sid());
  CPPUNIT_ASSERT_EQUAL(uint64_t(0), another.tableSize(testTable()));

  accessor().commit();

  CPPUNIT_ASSERT_EQUAL(uint64_t(7), another.tableSize(testTable()));
}

void 
CoreFeatureTest::
testReadNull()
{
  accessor().execute("insert into " + testTable() + " values (7, 'aaa')");
  accessor().execute("insert into " + testTable() + " values (NULL, 'zzz')");
  accessor().execute("insert into " + testTable() + " values (9, NULL)");

  struct Director : public sk::oci::abstract::Director {
    void processCursor(sk::oci::Cursor& cursor) const {
      cursor.setCapacity(5);

      const sk::oci::Data& id = cursor.boundData((cursor.bindIntAt(1)));
      const sk::oci::Data& name = cursor.boundData((cursor.bindCharsAt(2, 40)));

      CPPUNIT_ASSERT_EQUAL(3U, cursor.fetch());

      CPPUNIT_ASSERT_EQUAL(7U, id.piece(0).intValue());
      CPPUNIT_ASSERT_EQUAL(9U, id.piece(2).intValue());
      CPPUNIT_ASSERT_EQUAL("aaa", name.piece(0).stringValue());
      CPPUNIT_ASSERT_EQUAL("zzz", name.piece(1).stringValue());

      CPPUNIT_ASSERT(id.piece(0).isNull() == false);
      CPPUNIT_ASSERT(id.piece(1).isNull() == true);

      CPPUNIT_ASSERT(name.piece(1).isNull() == false);
      CPPUNIT_ASSERT(name.piece(2).isNull() == true);
    }
  };
  accessor().execute("select * from " + testTable(), Director());
}

void
CoreFeatureTest::
testWriteNull()
{
  struct InsertingDirector : public sk::oci::abstract::Director {
    void prepareStatement(sk::oci::Statement& statement) const {
      statement.setCapacity(2);

      sk::oci::Data& id = statement.boundMutableData(statement.bindIntTag(":id", sk::util::Integers() << 0 << 8));
      sk::oci::Data& name = statement.boundMutableData(statement.bindCharsTag(":name", 40, sk::util::Strings() << "abc" << ""));

      id.piece(0).setNull(true);
      name.piece(1).setNull(true);
    }
  };
  accessor().execute("insert into " + testTable() + " values (:id, :name)", InsertingDirector());

  struct SelectingDirector : public sk::oci::abstract::Director {
    void processCursor(sk::oci::Cursor& cursor) const {
      cursor.setCapacity(4);

      const sk::oci::Data& id = cursor.boundData(cursor.bindIntAt(1));
      const sk::oci::Data& name = cursor.boundData(cursor.bindCharsAt(2, 40));

      CPPUNIT_ASSERT_EQUAL(2U, cursor.fetch());

      CPPUNIT_ASSERT(id.piece(0).isNull() == true);
      CPPUNIT_ASSERT(id.piece(1).isNull() == false);
      CPPUNIT_ASSERT(name.piece(0).isNull() == false);
      CPPUNIT_ASSERT(name.piece(1).isNull() == true);

      CPPUNIT_ASSERT_EQUAL(8U, id.piece(1).intValue());
      CPPUNIT_ASSERT_EQUAL("abc", name.piece(0).stringValue());
    }
  };
  accessor().execute("select * from " + testTable(), SelectingDirector());
}
