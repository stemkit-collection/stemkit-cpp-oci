/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#include "ExceptionTest.h"
#include <sk/oci/Exception.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::oci::tests::ExceptionTest);

sk::oci::tests::ExceptionTest::
ExceptionTest()
{
}

sk::oci::tests::ExceptionTest::
~ExceptionTest()
{
}

void
sk::oci::tests::ExceptionTest::
setUp()
{
}

void
sk::oci::tests::ExceptionTest::
tearDown()
{
}

void
sk::oci::tests::ExceptionTest::
testBasics()
{
  try {
    throw sk::oci::Exception("abc", "he-he");
  }
  catch(const sk::oci::Exception& exception) {
    CPPUNIT_ASSERT_EQUAL("ERROR: abc: he-he", exception.what());
  }
}

void
sk::oci::tests::ExceptionTest::
testOriginNormalizeFunction()
{
  try {
    throw sk::oci::Exception("func(hello)", "he-he");
  }
  catch(const sk::oci::Exception& exception) {
    CPPUNIT_ASSERT_EQUAL("ERROR: func: he-he", exception.what());
  }
}

void
sk::oci::tests::ExceptionTest::
testOriginNormalizeNamespace()
{
  try {
    throw sk::oci::Exception("aaa::bbb::ccc", "he-he");
  }
  catch(const sk::oci::Exception& exception) {
    CPPUNIT_ASSERT_EQUAL("ERROR: ccc: he-he", exception.what());
  }
}

void
sk::oci::tests::ExceptionTest::
testOriginNormalizeBoth()
{
  try {
    throw sk::oci::Exception("aaa::bbb::zzz(312)", "he-he");
  }
  catch(const sk::oci::Exception& exception) {
    CPPUNIT_ASSERT_EQUAL("ERROR: zzz: he-he", exception.what());
  }
}
