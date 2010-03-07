/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "DescribeTableTest.h"
#include "App.h"
#include "app/Fixture.h"
#include <sk/oci/info/Table.h>
#include <sk/oci/info/Column.h>

CPPUNIT_TEST_SUITE_REGISTRATION(DescribeTableTest);

DescribeTableTest::
DescribeTableTest()
{
}

DescribeTableTest::
~DescribeTableTest()
{
}

void
DescribeTableTest::
setUp()
{
}

void
DescribeTableTest::
tearDown()
{
}

void
DescribeTableTest::
testDefaultTable()
{
  app::Fixture& fixture = test::App::fixture();
  sk::oci::Accessor& accessor = fixture.dbAccessor();
  const sk::oci::info::Table table = accessor.describeTable(fixture.testTable());

  CPPUNIT_ASSERT_EQUAL(fixture.testTable(), table.getName());
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
