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
#include <sk/oci/info/Type.h>

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
testQueries()
{
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isNumber() == true);
  CPPUNIT_ASSERT(info::Type::SK_VARCHAR2.isVarChar2() == true);
  CPPUNIT_ASSERT(info::Type::SK_VARCHAR.isVarChar() == true);
  CPPUNIT_ASSERT(info::Type::SK_CHAR.isChar() == true);
  CPPUNIT_ASSERT(info::Type::SK_REF.isRef() == true);
  CPPUNIT_ASSERT(info::Type::SK_DATE.isDate() == true);
  CPPUNIT_ASSERT(info::Type::SK_REAL.isReal() == true);
  CPPUNIT_ASSERT(info::Type::SK_DOUBLE.isDouble() == true);
  CPPUNIT_ASSERT(info::Type::SK_FLOAT.isFloat() == true);
  CPPUNIT_ASSERT(info::Type::SK_DECIMAL.isDecimal() == true);
  CPPUNIT_ASSERT(info::Type::SK_OCTET.isOctet() == true);
  CPPUNIT_ASSERT(info::Type::SK_INTEGER.isInteger() == true);
  CPPUNIT_ASSERT(info::Type::SK_SMALLINT.isSmallInt() == true);
  CPPUNIT_ASSERT(info::Type::SK_RAW.isRaw() == true);
  CPPUNIT_ASSERT(info::Type::SK_VARRAY.isVarray() == true);
  CPPUNIT_ASSERT(info::Type::SK_TABLE.isTable() == true);
  CPPUNIT_ASSERT(info::Type::SK_CLOB.isClob() == true);
  CPPUNIT_ASSERT(info::Type::SK_BLOB.isBlob() == true);
  CPPUNIT_ASSERT(info::Type::SK_BFILE.isBfile() == true);
  CPPUNIT_ASSERT(info::Type::SK_OBJECT.isObject() == true);
  CPPUNIT_ASSERT(info::Type::SK_NAMEDCOLLECTION.isNamedCollection() == true);
}

void
sk::oci::info::tests::TypeTest::
testOppositeQueries()
{
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isNumber() == true);
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isVarChar2() == false);
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isVarChar() == false);
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isChar() == false);
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isRef() == false);
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isDate() == false);
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isReal() == false);
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isDouble() == false);
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isFloat() == false);
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isDecimal() == false);
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isOctet() == false);
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isInteger() == false);
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isSmallInt() == false);
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isRaw() == false);
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isVarray() == false);
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isTable() == false);
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isClob() == false);
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isBlob() == false);
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isBfile() == false);
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isObject() == false);
  CPPUNIT_ASSERT(info::Type::SK_NUMBER.isNamedCollection() == false);
}
