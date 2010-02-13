/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "TypeTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(sk::oci::info::tests::TypeTest);

sk::oci::info::tests::TypeTest::
TypeTest()
{
}

sk::oci::info::tests::TypeTest::
~TypeTest()
{
}

void
sk::oci::info::tests::TypeTest::
setUp()
{
}

void
sk::oci::info::tests::TypeTest::
tearDown()
{
}

void
sk::oci::info::tests::TypeTest::
testBasics()
{
  CPPUNIT_ASSERT_EQUAL(true, false);
}
