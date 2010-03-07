/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _INSERTSELECTTEST_H_
#define _INSERTSELECTTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class InsertSelectTest
  : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(InsertSelectTest);
    CPPUNIT_TEST(testSelectList);
    CPPUNIT_TEST(testRowCountAfterInsert);
    CPPUNIT_TEST(testInsertSelect);
  CPPUNIT_TEST_SUITE_END();

  public:
    InsertSelectTest();
    virtual ~InsertSelectTest();

    void setUp();
    void tearDown();
    void testSelectList();
    void testRowCountAfterInsert();
    void testInsertSelect();

  private:
    InsertSelectTest(const InsertSelectTest& other);
    InsertSelectTest& operator = (const InsertSelectTest& other);
};

#endif /* _INSERTSELECTTEST_H_ */
