/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_BIND_DATATEST_H_
#define _SK_OCI_DB_BIND_DATATEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sk {
  namespace oci {
    namespace db {
      namespace bind {
        class DataTest
          : public CppUnit::TestFixture
        {
          CPPUNIT_TEST_SUITE(sk::oci::db::bind::DataTest);
            CPPUNIT_TEST(testBasicsSingle);
            CPPUNIT_TEST(testBasicsCompound);
          CPPUNIT_TEST_SUITE_END();
        
          public:
            DataTest();
            virtual ~DataTest();
        
            void setUp();
            void tearDown();
            void testBasicsSingle();
            void testBasicsCompound();
        
          private:
            DataTest(const DataTest& other);
            DataTest& operator = (const DataTest& other);
        };
      }
    }
  }
}

#endif /* _SK_OCI_DB_BIND_DATATEST_H_ */
