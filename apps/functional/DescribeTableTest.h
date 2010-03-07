/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _DESCRIBETABLETEST_H_
#define _DESCRIBETABLETEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class DescribeTableTest
  : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(DescribeTableTest);
    CPPUNIT_TEST(testDefaultTable);
  CPPUNIT_TEST_SUITE_END();

  public:
    DescribeTableTest();
    virtual ~DescribeTableTest();

    void setUp();
    void tearDown();
    void testDefaultTable();

  private:
    DescribeTableTest(const DescribeTableTest& other);
    DescribeTableTest& operator = (const DescribeTableTest& other);
};

#endif /* _DESCRIBETABLETEST_H_ */
