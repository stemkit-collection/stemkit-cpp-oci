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
#include "../IntData.h"
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
testBasicsSingle()
{
  sk::oci::db::bind::CharsData data(0, 2, 10);
  CPPUNIT_ASSERT_EQUAL(1, data.capacity());
  CPPUNIT_ASSERT_EQUAL(ub4(2), data.position());
  CPPUNIT_ASSERT_EQUAL(10, data.valueSize());
  CPPUNIT_ASSERT_EQUAL(ub2(SQLT_STR), data.type());
  
  CPPUNIT_ASSERT_EQUAL(0, data.tagSize());
  CPPUNIT_ASSERT_THROW(data.tagPointer(), sk::util::IllegalStateException);

  CPPUNIT_ASSERT_EQUAL(3, data.descriptorSize());
  CPPUNIT_ASSERT_EQUAL(10, data.depotSize());

  CPPUNIT_ASSERT(data.piece(0).isNull() == true);
  CPPUNIT_ASSERT_EQUAL(0U, data.piece(0).size());
  CPPUNIT_ASSERT_THROW(data.piece(1), sk::util::IndexOutOfBoundsException);
}

void
sk::oci::db::bind::DataTest::
testBasicsCompound()
{
  sk::oci::db::bind::IntData data(3, "abcd");
  CPPUNIT_ASSERT_EQUAL(3, data.capacity());
  CPPUNIT_ASSERT_EQUAL(ub4(0), data.position());
  CPPUNIT_ASSERT_EQUAL(4, data.valueSize());
  CPPUNIT_ASSERT_EQUAL(ub2(SQLT_INT), data.type());
  CPPUNIT_ASSERT_EQUAL(4, data.tagSize());
  CPPUNIT_ASSERT_EQUAL("abcd", reinterpret_cast<const char*>(data.tagPointer()));

  CPPUNIT_ASSERT_EQUAL(9, data.descriptorSize());
  CPPUNIT_ASSERT_EQUAL(17, data.depotSize());

  CPPUNIT_ASSERT(data.piece(0).isNull() == true);
  CPPUNIT_ASSERT_EQUAL(0U, data.piece(0).size());
  CPPUNIT_ASSERT(data.piece(1).isNull() == true);
  CPPUNIT_ASSERT_EQUAL(0U, data.piece(1).size());
  CPPUNIT_ASSERT(data.piece(2).isNull() == true);
  CPPUNIT_ASSERT_EQUAL(0U, data.piece(2).size());

  CPPUNIT_ASSERT_THROW(data.piece(3), sk::util::IndexOutOfBoundsException);
}

void
sk::oci::db::bind::DataTest::
testIndicator()
{
  sk::oci::db::bind::IntData data(3, 1);
  CPPUNIT_ASSERT_EQUAL(3, data.capacity());

  CPPUNIT_ASSERT(data.piece(0).isNull() == true);
  CPPUNIT_ASSERT(data.piece(0).isTruncated() == false);
  CPPUNIT_ASSERT(data.piece(1).isNull() == true);
  CPPUNIT_ASSERT(data.piece(1).isTruncated() == false);
  CPPUNIT_ASSERT(data.piece(2).isNull() == true);
  CPPUNIT_ASSERT(data.piece(2).isTruncated() == false);

  *(data.indicatorPointer() + 0) = 0;
  *(data.indicatorPointer() + 1) = 0;
  *(data.indicatorPointer() + 2) = 0;

  CPPUNIT_ASSERT(data.piece(0).isNull() == false);
  CPPUNIT_ASSERT(data.piece(0).isTruncated() == false);
  CPPUNIT_ASSERT(data.piece(1).isNull() == false);
  CPPUNIT_ASSERT(data.piece(1).isTruncated() == false);
  CPPUNIT_ASSERT(data.piece(2).isNull() == false);
  CPPUNIT_ASSERT(data.piece(2).isTruncated() == false);

  *(data.indicatorPointer() + 0) = -2;
  *(data.indicatorPointer() + 1) = -2;
  *(data.indicatorPointer() + 2) = -2;

  CPPUNIT_ASSERT(data.piece(0).isNull() == false);
  CPPUNIT_ASSERT(data.piece(0).isTruncated() == true);
  CPPUNIT_ASSERT(data.piece(1).isNull() == false);
  CPPUNIT_ASSERT(data.piece(1).isTruncated() == true);
  CPPUNIT_ASSERT(data.piece(2).isNull() == false);
  CPPUNIT_ASSERT(data.piece(2).isTruncated() == true);

  *(data.indicatorPointer() + 0) = 3;
  *(data.indicatorPointer() + 1) = 3;
  *(data.indicatorPointer() + 2) = 3;

  CPPUNIT_ASSERT(data.piece(0).isNull() == false);
  CPPUNIT_ASSERT(data.piece(0).isTruncated() == true);
  CPPUNIT_ASSERT(data.piece(1).isNull() == false);
  CPPUNIT_ASSERT(data.piece(1).isTruncated() == true);
  CPPUNIT_ASSERT(data.piece(2).isNull() == false);
  CPPUNIT_ASSERT(data.piece(2).isTruncated() == true);

  *(data.indicatorPointer() + 0) = 0;
  *(data.indicatorPointer() + 1) = 0;
  *(data.indicatorPointer() + 2) = 0;

  CPPUNIT_ASSERT(data.piece(0).isNull() == false);
  CPPUNIT_ASSERT(data.piece(0).isTruncated() == false);
  CPPUNIT_ASSERT(data.piece(1).isNull() == false);
  CPPUNIT_ASSERT(data.piece(1).isTruncated() == false);
  CPPUNIT_ASSERT(data.piece(2).isNull() == false);
  CPPUNIT_ASSERT(data.piece(2).isTruncated() == false);
}
