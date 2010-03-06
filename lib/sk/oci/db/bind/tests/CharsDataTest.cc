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

#include <sk/oci/BindSizeException.h>

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

void
sk::oci::db::bind::CharsDataTest::
testMultiValue()
{
  sk::oci::db::bind::CharsData data(3, 1, 10, sk::util::Strings() << "aaaa" << "bbb" << "ccccc");

  CPPUNIT_ASSERT_EQUAL(5U, data.piece(0).size());
  CPPUNIT_ASSERT_EQUAL(4U, data.piece(1).size());
  CPPUNIT_ASSERT_EQUAL(6U, data.piece(2).size());

  CPPUNIT_ASSERT_EQUAL("aaaa", data.piece(0).stringValue());
  CPPUNIT_ASSERT_EQUAL("bbb", data.piece(1).stringValue());
  CPPUNIT_ASSERT_EQUAL("ccccc", data.piece(2).stringValue());

  data.piece(1).setCharsValue("1234567890987654321");

  CPPUNIT_ASSERT_EQUAL(10U, data.piece(1).size());
  CPPUNIT_ASSERT_EQUAL("123456789", data.piece(1).stringValue());
}

void
sk::oci::db::bind::CharsDataTest::
testMoreBindValues()
{
  try {
    sk::oci::db::bind::CharsData(1, 3, 10, sk::util::Strings() << "aaa" << "bbb");
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::oci::BindSizeException& exception) {
    CPPUNIT_ASSERT_EQUAL(1U, exception.getExpected());
    CPPUNIT_ASSERT_EQUAL(2U, exception.getActual());
  }

  try {
    sk::oci::db::bind::CharsData(2, 3, 10, sk::util::Strings() << "aaa" << "bbb" << "zzz");
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::oci::BindSizeException& exception) {
    CPPUNIT_ASSERT_EQUAL(2U, exception.getExpected());
    CPPUNIT_ASSERT_EQUAL(3U, exception.getActual());
  }
}

void
sk::oci::db::bind::CharsDataTest::
testLessBindValues()
{
  try {
    sk::oci::db::bind::CharsData(3, 1, 10, sk::util::Strings() << "aaa" << "bbb");
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::oci::BindSizeException& exception) {
    CPPUNIT_ASSERT_EQUAL(3U, exception.getExpected());
    CPPUNIT_ASSERT_EQUAL(2U, exception.getActual());
  }

  try {
    sk::oci::db::bind::CharsData(3, 1, 10, "zzz");
    CPPUNIT_FAIL("No expected exception");
  }
  catch(const sk::oci::BindSizeException& exception) {
    CPPUNIT_ASSERT_EQUAL(3U, exception.getExpected());
    CPPUNIT_ASSERT_EQUAL(1U, exception.getActual());
  }
}
