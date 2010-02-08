/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_TESTS_EXCEPTIONTEST_H_
#define _SK_OCI_TESTS_EXCEPTIONTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace oci {
    namespace tests {
      class ExceptionTest
        : public CppUnit::TestFixture
      {
        CPPUNIT_TEST_SUITE(sk::oci::tests::ExceptionTest);
          CPPUNIT_TEST(testBasics);
          CPPUNIT_TEST(testOriginNormalize);
        CPPUNIT_TEST_SUITE_END();
      
        public:
          ExceptionTest();
          virtual ~ExceptionTest();
      
          void setUp();
          void tearDown();
          void testBasics();
          void testOriginNormalize();
      
        private:
          ExceptionTest(const ExceptionTest& other);
          ExceptionTest& operator = (const ExceptionTest& other);
      };
    }
  }
}

#endif /* _SK_OCI_TESTS_EXCEPTIONTEST_H_ */
