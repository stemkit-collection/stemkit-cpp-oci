/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_DATA_H_
#define _SK_OCI_DB_DATA_H_

#include <sk/util/Object.h>
#include <oci.h>

namespace sk {
  namespace oci {
    namespace db {
      class Data 
        : public virtual sk::util::Object
      {
        typedef OCIBind* oci_bind_handle;
        typedef OCIDefine* oci_define_handle;

        public:
          Data();
          virtual ~Data();

          oci_bind_handle& bindHandle();
          oci_define_handle& defineHandle();

          ub4 position() const;
          ub4 index() const;

          dvoid* valuePointer();
          sb4 valueSize() const;
          ub2 type() const;
          dvoid* indicatorPointer();
          const text* tagPointer() const;
          sb4 tagSize() const;
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          Data(const Data& other);
          Data& operator = (const Data& other);
      };
    }
  }
}

#endif /* _SK_OCI_DB_DATA_H_ */
