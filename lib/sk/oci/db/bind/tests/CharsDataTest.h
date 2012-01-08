/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_BIND_CHARSDATATEST_H_
#define _SK_OCI_DB_BIND_CHARSDATATEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace oci {
    namespace db {
      namespace bind {
        class CharsDataTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::oci::db::bind::CharsDataTest);
            CPPUNIT_TEST(testInfo);
            CPPUNIT_TEST(testMultiValue);
            CPPUNIT_TEST(testMoreBindValues);
            CPPUNIT_TEST(testLessBindValues);
          CPPUNIT_TEST_SUITE_END();

          public:
            CharsDataTest();
            virtual ~CharsDataTest();

            void setUp();
            void tearDown();
            void testInfo();
            void testMultiValue();
            void testMoreBindValues();
            void testLessBindValues();

          private:
            CharsDataTest(const CharsDataTest& other);
            CharsDataTest& operator = (const CharsDataTest& other);
        };
      }
    }
  }
}

#endif /* _SK_OCI_DB_BIND_CHARSDATATEST_H_ */
