/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "CoreFeaturesTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(CoreFeaturesTest);

#include "App.h"
#include "app/Fixture.h"
#include <sk/oci/info/Table.h>
#include <sk/oci/info/Column.h>
#include <sk/oci/abstract/Director.h>
#include <sk/util/IndexOutOfBoundsException.h>
#include <sk/oci/TruncatedColumnException.h>
#include <sk/oci/BindSizeException.h>
#include <sk/oci/Data.h>

#include <sk/oci/db/Accessor.h>

CoreFeaturesTest::
CoreFeaturesTest()
{
}

CoreFeaturesTest::
~CoreFeaturesTest()
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
CoreFeaturesTest::
setUp()
{
  fixture().dropTestTable();
  fixture().createTestTable("id integer, name varchar2(40)");
}

void
CoreFeaturesTest::
tearDown()
{
}

void
CoreFeaturesTest::
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
CoreFeaturesTest::
testSelectList()
{
  struct Director : public sk::oci::abstract::Director {
    void processCursor(sk::oci::Cursor& cursor) const {
      CPPUNIT_ASSERT_EQUAL(2u, cursor.columnCount());
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
CoreFeaturesTest::
testRowCountAfterInsert()
{
  CPPUNIT_ASSERT_EQUAL(0u, accessor().tableSize(testTable()));
  accessor().execute("insert into " + testTable() + " values (1, 'abc')");
  accessor().execute("insert into " + testTable() + " values (2, 'zzz')");
  CPPUNIT_ASSERT_EQUAL(2u, accessor().tableSize(testTable()));

  struct Director : public sk::oci::abstract::Director {
    void prepareStatement(sk::oci::Statement& statement) const {
      statement.setCapacity(5);
    }
  };
  accessor().execute("insert into " + testTable() + " values (3, 'uuu')", Director());
  CPPUNIT_ASSERT_EQUAL(7u, accessor().tableSize(testTable()));
}

void 
CoreFeaturesTest::
generateInsertsOneByOne(int amount, const sk::util::String& data) 
{
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

void 
CoreFeaturesTest::
generateInsertsAsArray(int amount, const sk::util::String& data) 
{
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

void 
CoreFeaturesTest::
selectAllOneByOne(sk::util::Strings& depot) 
{
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

void 
CoreFeaturesTest::
selectAllAsArray(int chunkSize, sk::util::Strings& depot) 
{
  struct Director : public sk::oci::abstract::Director {
    Director(int chunkSize, sk::util::Strings& depot) 
      : _chunkSize(chunkSize), _depot(depot) {}

    void processCursor(sk::oci::Cursor& cursor) const {
      cursor.setCapacity(_chunkSize);

      const sk::oci::Data& num = cursor.boundData(cursor.bindIntAt(1));
      const sk::oci::Data& str = cursor.boundData(cursor.bindCharsAt(2, 40));

      for(uint32_t rows = cursor.fetch(); rows != 0; rows = cursor.fetch()) {
        for(int index=0; index < rows; ++index) {
          _depot << sk::util::String::valueOf(num.piece(index).intValue()) + ':' + str.piece(index).stringValue();
        }
      }
    }
    const int _chunkSize;
    sk::util::Strings& _depot;
  };
  accessor().execute("select * from " + testTable(), Director(chunkSize, depot));
}

void
CoreFeaturesTest::
testInsertAsIterations()
{
  generateInsertsOneByOne(5, "a");

  sk::util::Strings depot;
  selectAllAsArray(3, depot);

  CPPUNIT_ASSERT_EQUAL(5, depot.size());

  CPPUNIT_ASSERT_EQUAL("1:a", depot.get(0));
  CPPUNIT_ASSERT_EQUAL("2:aa", depot.get(1));
  CPPUNIT_ASSERT_EQUAL("3:aaa", depot.get(2));
  CPPUNIT_ASSERT_EQUAL("4:aaaa", depot.get(3));
  CPPUNIT_ASSERT_EQUAL("5:aaaaa", depot.get(4));
}

void
CoreFeaturesTest::
testInsertAsArray()
{
  generateInsertsAsArray(3, "b");

  sk::util::Strings depot;
  selectAllOneByOne(depot);

  CPPUNIT_ASSERT_EQUAL(3, depot.size());

  CPPUNIT_ASSERT_EQUAL("1:b", depot.get(0));
  CPPUNIT_ASSERT_EQUAL("2:bb", depot.get(1));
  CPPUNIT_ASSERT_EQUAL("3:bbb", depot.get(2));
}

void 
CoreFeaturesTest::
testRollback()
{
  CPPUNIT_ASSERT_EQUAL(0u, accessor().tableSize(testTable()));
  generateInsertsOneByOne(7, "z");
  CPPUNIT_ASSERT_EQUAL(7u, accessor().tableSize(testTable()));

  accessor().rollback();

  CPPUNIT_ASSERT_EQUAL(0u, accessor().tableSize(testTable()));
}

void 
CoreFeaturesTest::
testRollbackAfterCommit()
{
  CPPUNIT_ASSERT_EQUAL(0u, accessor().tableSize(testTable()));
  generateInsertsAsArray(7, "z");
  CPPUNIT_ASSERT_EQUAL(7u, accessor().tableSize(testTable()));

  accessor().commit();
  accessor().rollback();

  CPPUNIT_ASSERT_EQUAL(7u, accessor().tableSize(testTable()));
}

void 
CoreFeaturesTest::
testCommit()
{
  CPPUNIT_ASSERT_EQUAL(0u, accessor().tableSize(testTable()));
  generateInsertsAsArray(7, "z");
  CPPUNIT_ASSERT_EQUAL(7u, accessor().tableSize(testTable()));

  sk::oci::db::Accessor another(fixture().user(), fixture().password(), fixture().sid());
  CPPUNIT_ASSERT_EQUAL(0u, another.tableSize(testTable()));

  accessor().commit();

  CPPUNIT_ASSERT_EQUAL(7u, another.tableSize(testTable()));
}

void 
CoreFeaturesTest::
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

      CPPUNIT_ASSERT_EQUAL(3u, cursor.fetch());

      CPPUNIT_ASSERT_EQUAL(7, id.piece(0).intValue());
      CPPUNIT_ASSERT_EQUAL(9, id.piece(2).intValue());
      CPPUNIT_ASSERT_EQUAL("aaa", name.piece(0).stringValue());
      CPPUNIT_ASSERT_EQUAL("zzz", name.piece(1).stringValue());

      CPPUNIT_ASSERT(id.piece(0).isNull() == false);
      CPPUNIT_ASSERT(id.piece(1).isNull() == true);

      CPPUNIT_ASSERT(name.piece(1).isNull() == false);
      CPPUNIT_ASSERT(name.piece(2).isNull() == true);

      // The following must not be set in this case as useColumnCodes()
      // was not set.
      CPPUNIT_ASSERT(cursor.hasInfo() == false);
      CPPUNIT_ASSERT_EQUAL(0u, id.piece(1).columnCode());
      CPPUNIT_ASSERT_EQUAL(0u, name.piece(2).columnCode());
    }
  };
  accessor().execute("select * from " + testTable(), Director());
}

void
CoreFeaturesTest::
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

      CPPUNIT_ASSERT_EQUAL(2u, cursor.fetch());

      CPPUNIT_ASSERT(id.piece(0).isNull() == true);
      CPPUNIT_ASSERT(id.piece(1).isNull() == false);
      CPPUNIT_ASSERT(name.piece(0).isNull() == false);
      CPPUNIT_ASSERT(name.piece(1).isNull() == true);

      CPPUNIT_ASSERT_EQUAL(8, id.piece(1).intValue());
      CPPUNIT_ASSERT_EQUAL("abc", name.piece(0).stringValue());
    }
  };
  accessor().execute("select * from " + testTable(), SelectingDirector());
}

void
CoreFeaturesTest::
testNullColumCodes()
{
  accessor().execute("insert into " + testTable() + " values (NULL, 'abc')");
  accessor().execute("insert into " + testTable() + " values (3, NULL)");

  struct Director : public sk::oci::abstract::Director {
    void processCursor(sk::oci::Cursor& cursor) const {
      const sk::oci::Data& id = cursor.boundData(cursor.bindIntAt(1));
      const sk::oci::Data& name = cursor.boundData(cursor.bindCharsAt(2, 40));

      CPPUNIT_ASSERT_EQUAL(1u, cursor.fetch());

      CPPUNIT_ASSERT(cursor.hasInfo() == false);
      CPPUNIT_ASSERT(id.isNull() == true);
      CPPUNIT_ASSERT_EQUAL(0u, id.columnCode());
      {
        cursor.useColumnCodes(true);
        const sk::oci::Data& id = cursor.boundData(cursor.bindIntAt(1));
        const sk::oci::Data& name = cursor.boundData(cursor.bindCharsAt(2, 40));

        CPPUNIT_ASSERT_EQUAL(1u, cursor.fetch());

        CPPUNIT_ASSERT(cursor.hasInfo() == false);
        CPPUNIT_ASSERT(name.isNull() == true);
        CPPUNIT_ASSERT(id.isNull() == false);
        CPPUNIT_ASSERT_EQUAL(1405u, name.columnCode());
        CPPUNIT_ASSERT_EQUAL(0u, id.columnCode());
      }
      CPPUNIT_ASSERT_EQUAL(0u, cursor.fetch());
      CPPUNIT_ASSERT_EQUAL(2u, cursor.rowCount());
    }
  };
  accessor().execute("select * from " + testTable(), Director());
}

void
CoreFeaturesTest::
testTruncateException()
{
  accessor().execute("insert into " + testTable() + " values (1, '12345678901234567890')");

  struct Director : public sk::oci::abstract::Director {
    void processCursor(sk::oci::Cursor& cursor) const {
      const sk::oci::Data& id = cursor.boundData(cursor.bindIntAt(1));
      const sk::oci::Data& name = cursor.boundData(cursor.bindCharsAt(2, 15));

      try {
        cursor.fetch();
        CPPUNIT_FAIL("No expected exception");
      }
      catch(const sk::oci::TruncatedColumnException& exception) {
        CPPUNIT_ASSERT(id.isTruncated() == false);
        CPPUNIT_ASSERT(name.isTruncated() == true);
        CPPUNIT_ASSERT_EQUAL(14u, name.size());
        CPPUNIT_ASSERT_EQUAL(0u, name.columnCode());
      }
      CPPUNIT_ASSERT_EQUAL(1u, cursor.rowCount());
    }
  };
  accessor().execute("select * from " + testTable(), Director());
}

void
CoreFeaturesTest::
testTruncateNoException()
{
  accessor().execute("insert into " + testTable() + " values (1, '12345678901234567890')");

  struct Director : public sk::oci::abstract::Director {
    void processCursor(sk::oci::Cursor& cursor) const {
      cursor.useTruncate(true);

      const sk::oci::Data& id = cursor.boundData(cursor.bindIntAt(1));
      const sk::oci::Data& name = cursor.boundData(cursor.bindCharsAt(2, 15));

      CPPUNIT_ASSERT_EQUAL(1u, cursor.fetch());

      CPPUNIT_ASSERT(id.isTruncated() == false);
      CPPUNIT_ASSERT(name.isTruncated() == true);
      CPPUNIT_ASSERT_EQUAL(14u, name.size());
      
      CPPUNIT_ASSERT(cursor.hasInfo() == false);
      CPPUNIT_ASSERT_EQUAL(0u, name.columnCode());

      CPPUNIT_ASSERT_EQUAL(1u, cursor.rowCount());
    }
  };
  accessor().execute("select * from " + testTable(), Director());
}

void
CoreFeaturesTest::
testTruncateColumnCodes()
{
  accessor().execute("insert into " + testTable() + " values (1, '12345678901234567890')");

  struct Director : public sk::oci::abstract::Director {
    void processCursor(sk::oci::Cursor& cursor) const {
      cursor.useTruncate(true);
      cursor.useColumnCodes(true);

      const sk::oci::Data& id = cursor.boundData(cursor.bindIntAt(1));
      const sk::oci::Data& name = cursor.boundData(cursor.bindCharsAt(2, 15));

      CPPUNIT_ASSERT_EQUAL(1u, cursor.fetch());

      CPPUNIT_ASSERT(id.isTruncated() == false);
      CPPUNIT_ASSERT(name.isTruncated() == true);
      CPPUNIT_ASSERT_EQUAL(14u, name.size());
      
      CPPUNIT_ASSERT(cursor.hasInfo() == true);
      CPPUNIT_ASSERT_EQUAL(1406u, name.columnCode());

      CPPUNIT_ASSERT_EQUAL(1u, cursor.rowCount());
    }
  };
  accessor().execute("select * from " + testTable(), Director());
}

void 
CoreFeaturesTest::
testNoData()
{
  struct Director : public sk::oci::abstract::Director {
    void processCursor(sk::oci::Cursor& cursor) const {
      const sk::oci::Data& id = cursor.boundData(cursor.bindIntAt(1));
      const sk::oci::Data& name = cursor.boundData(cursor.bindCharsAt(2, 15));

      CPPUNIT_ASSERT_EQUAL(0u, cursor.fetch());
    }
  };
  accessor().execute("select * from " + testTable(), Director());
}

void
CoreFeaturesTest::
testBindSizeMatch()
{
  struct Director : public sk::oci::abstract::Director {
    void prepareStatement(sk::oci::Statement& statement) const {
      statement.setCapacity(3);

      try {
        statement.bindIntAt(1, sk::util::Integers() << 1 << 2 << 3 << 4);
        CPPUNIT_FAIL("No expected exception");
      }
      catch(const sk::oci::BindSizeException& exception) {
        CPPUNIT_ASSERT_EQUAL(3u, exception.getExpected());
        CPPUNIT_ASSERT_EQUAL(4u, exception.getActual());
      }

      try {
        statement.bindCharsAt(2, 15, sk::util::Strings() << "aaa" << "bbb");;
        CPPUNIT_FAIL("No expected exception");
      }
      catch(const sk::oci::BindSizeException& exception) {
        CPPUNIT_ASSERT_EQUAL(3u, exception.getExpected());
        CPPUNIT_ASSERT_EQUAL(2u, exception.getActual());
      }

      statement.bindIntAt(1, sk::util::Integers() << 1 << 2 << 3);
      statement.bindCharsAt(2, 15, sk::util::Strings() << "aaa" << "bbb" << "ccc");;
    }
  };
  accessor().execute("insert into " + testTable() + " values (:id, :name)", Director());

  sk::util::Strings depot;
  selectAllOneByOne(depot);

  CPPUNIT_ASSERT_EQUAL(3, depot.size());
  CPPUNIT_ASSERT_EQUAL("1:aaa", depot.get(0));
  CPPUNIT_ASSERT_EQUAL("2:bbb", depot.get(1));
  CPPUNIT_ASSERT_EQUAL("3:ccc", depot.get(2));
}
