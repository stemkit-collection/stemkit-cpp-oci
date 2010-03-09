/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _COREFEATURESTEST_H_
#define _COREFEATURESTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class CoreFeaturesTest
  : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(CoreFeaturesTest);
    CPPUNIT_TEST(testDescribeTable);
    CPPUNIT_TEST(testSelectList);
    CPPUNIT_TEST(testRowCountAfterInsert);
    CPPUNIT_TEST(testInsertAsIterations);
    CPPUNIT_TEST(testInsertAsArray);
    CPPUNIT_TEST(testRollback);
    CPPUNIT_TEST(testRollbackAfterCommit);
    CPPUNIT_TEST(testCommit);
    CPPUNIT_TEST(testReadNull);
    CPPUNIT_TEST(testWriteNull);
    CPPUNIT_TEST(testNullColumCodes);
  CPPUNIT_TEST_SUITE_END();

  public:
    CoreFeaturesTest();
    virtual ~CoreFeaturesTest();

    void setUp();
    void tearDown();

    void testDescribeTable();
    void testSelectList();
    void testRowCountAfterInsert();
    void testInsertAsIterations();
    void testInsertAsArray();
    void testRollback();
    void testRollbackAfterCommit();
    void testCommit();
    void testReadNull();
    void testWriteNull();
    void testNullColumCodes();

  private:
    CoreFeaturesTest(const CoreFeaturesTest& other);
    CoreFeaturesTest& operator = (const CoreFeaturesTest& other);

    void generateInsertsOneByOne(int amount, const sk::util::String& data);
    void generateInsertsAsArray(int amount, const sk::util::String& data);
    void selectAllOneByOne(sk::util::Strings& depot);
    void selectAllAsArray(int chunkSize, sk::util::Strings& depot);
};

#endif /* _COREFEATURESTEST_H_ */
