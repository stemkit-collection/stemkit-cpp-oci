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

#include <sk/oci/Data.h>
#include <oci.h>
#include <vector>

namespace sk {
  namespace oci {
    namespace db {
      class Data 
        : public virtual sk::oci::Data
      {
        typedef OCIBind* oci_bind_handle;
        typedef OCIDefine* oci_define_handle;

        public:
          Data(uint32_t capacity, uint32_t position, ub2 type, const void* value, int32_t size);
          virtual ~Data();

          oci_bind_handle& bindHandle();
          oci_define_handle& defineHandle();

          ub4 position() const;

          dvoid* valuePointer();
          sb4 valueSize() const;
          ub2 type() const;
          dvoid* indicatorPointer();
          const text* tagPointer() const;
          sb4 tagSize() const;
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
          // sk::oci::Data implementation.
          uint32_t intValue() const;
          const std::vector<char>& stringValue() const;
          bool isNull() const;
          bool isTruncated() const;

        private:
          Data(const Data& other);
          Data& operator = (const Data& other);

          union {
            oci_define_handle oci_define;
            oci_bind_handle oci_bind;
          } _handle;

          ub4 _position;
          ub2 _type;
          sb2 _indicator;
          std::vector<char> _value;
      };
    }
  }
}

#endif /* _SK_OCI_DB_DATA_H_ */
