/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "DataTest.h"
#include "../CharsData.h"
#include <sk/util/IndexOutOfBoundsException.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::oci::db::bind::DataTest);

sk::oci::db::bind::DataTest::
DataTest()
{
}

sk::oci::db::bind::DataTest::
~DataTest()
{
}

void
sk::oci::db::bind::DataTest::
setUp()
{
}

void
sk::oci::db::bind::DataTest::
tearDown()
{
}

void
sk::oci::db::bind::DataTest::
testBasics()
{
  sk::oci::db::bind::CharsData data(0, 2, 10);
  CPPUNIT_ASSERT_EQUAL(1, data.capacity());
  CPPUNIT_ASSERT_EQUAL(ub4(2), data.position());
  CPPUNIT_ASSERT_EQUAL(10, data.valueSize());
  CPPUNIT_ASSERT_EQUAL(ub2(SQLT_STR), data.type());
  CPPUNIT_ASSERT_EQUAL(0, data.tagSize());
  CPPUNIT_ASSERT_EQUAL(3, data.descriptorSize());
  CPPUNIT_ASSERT_EQUAL(10, data.depotSize());

  CPPUNIT_ASSERT(data.piece(0).isNull() == true);
  CPPUNIT_ASSERT_EQUAL(0U, data.piece(0).size());
  CPPUNIT_ASSERT_THROW(data.piece(1), sk::util::IndexOutOfBoundsException);
}
