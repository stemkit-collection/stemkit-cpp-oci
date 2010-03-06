/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "CharsDataTest.h"
#include "../CharsData.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::oci::db::bind::CharsDataTest);

sk::oci::db::bind::CharsDataTest::
CharsDataTest()
{
}

sk::oci::db::bind::CharsDataTest::
~CharsDataTest()
{
}

void
sk::oci::db::bind::CharsDataTest::
setUp()
{
}

void
sk::oci::db::bind::CharsDataTest::
tearDown()
{
}

void
sk::oci::db::bind::CharsDataTest::
testInfo()
{
  CPPUNIT_ASSERT_EQUAL("NULL", sk::oci::db::bind::CharsData(0, 1, 5).piece(0).info());
  CPPUNIT_ASSERT_EQUAL("\"zzz\"", sk::oci::db::bind::CharsData(0, 1, 5, "zzz").piece(0).info());

  sk::oci::db::bind::CharsData data(0, 1, 5, "zzz");
  *data.indicatorPointer() = 10;
  *data.columnCodePointer() = 1406;

  CPPUNIT_ASSERT_EQUAL("\"zzz\":truncated(6):code(1406)", data.piece(0).info());
}
