/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_INFO_TESTS_TYPETEST_H_
#define _SK_OCI_INFO_TESTS_TYPETEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace oci {
    namespace info {
      namespace tests {
        class TypeTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::oci::info::tests::TypeTest);
            CPPUNIT_TEST(testQueries);
            CPPUNIT_TEST(testOppositeQueries);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            TypeTest();
            virtual ~TypeTest();
        
            void setUp();
            void tearDown();
            void testQueries();
            void testOppositeQueries();
        
          private:
            TypeTest(const TypeTest& other);
            TypeTest& operator = (const TypeTest& other);
        };
      }
    }
  }
}

#endif /* _SK_OCI_INFO_TESTS_TYPETEST_H_ */
