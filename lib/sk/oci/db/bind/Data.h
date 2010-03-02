/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_BIND_DATA_H_
#define _SK_OCI_DB_BIND_DATA_H_

#include <sk/oci/Data.h>
#include <oci.h>

namespace sk {
  namespace oci {
    namespace db {
      namespace bind {
        class Data 
          : public virtual sk::oci::Data
        {
          typedef OCIBind* oci_bind_handle;
          typedef OCIDefine* oci_define_handle;

          public:
            Data(int capacity, uint32_t position, ub2 type, int size);
            Data(int capacity, const sk::util::String& tag, ub2 type, int size);

            oci_bind_handle& bindHandle();
            oci_define_handle& defineHandle();

            ub4 position() const;

            dvoid* valuePointer();
            sb4 valueSize() const;
            ub2 type() const;
            sb2* indicatorPointer();
            const text* tagPointer() const;
            sb4 tagSize() const;
            ub2* columnCodePointer();
            ub2* sizePointer();
        
            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;
        
            // sk::oci::Data implementation.
            const sk::util::String info() const;
            uint32_t& intValue();
            const uint32_t& intValue() const;
            sk::util::Container& stringValue();
            const sk::util::Container& stringValue() const;
            bool isNull() const;
            bool isTruncated() const;
            uint32_t size() const;
            uint32_t columnCode() const;
            void null(bool state);

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
            ub2 _columnCode;
            ub2 _size;
            sk::util::Container _value;
            sk::util::Container _tag;
        };
      }
    }
  }
}

#endif /* _SK_OCI_DB_BIND_DATA_H_ */
