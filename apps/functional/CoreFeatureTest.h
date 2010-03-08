/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _COREFEATURETEST_H_
#define _COREFEATURETEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class CoreFeatureTest
  : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(CoreFeatureTest);
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
  CPPUNIT_TEST_SUITE_END();

  public:
    CoreFeatureTest();
    virtual ~CoreFeatureTest();

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

  private:
    CoreFeatureTest(const CoreFeatureTest& other);
    CoreFeatureTest& operator = (const CoreFeatureTest& other);
};

#endif /* _COREFEATURETEST_H_ */
