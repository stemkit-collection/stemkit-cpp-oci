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

#include <sk/util/Object.h>
#include <sk/oci/Data.h>
#include <oci.h>

#include "Piece.h"

namespace sk {
  namespace oci {
    namespace db {
      namespace bind {
        class Data 
          : public virtual sk::util::Object
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
            int capacity() const;
        
            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;
        
            const sk::oci::Data& piece(int index) const;
            sk::oci::Data& piece(int index);

            const uint32_t& intValue(int index)const;
            const char* charsValue(int index) const;
            uint32_t size(int index) const;
            uint32_t columnCode(int index) const;

            bool isNull(int index) const;
            bool isTruncated(int index) const;

            void setIntValue(int index, uint32_t value);
            void setCharsValue(int index, const sk::util::String& value);
            void setNull(int index, bool state);

            const sk::util::String info(int index) const;

            virtual const sk::util::String inspect(int index) const = 0;
            virtual const sk::util::String toString(int index) const = 0;

          private:
            Data(const Data& other);
            Data& operator = (const Data& other);

            void setup(int capacity);

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
            int _capacity;

            bind::Piece _piece;
        };
      }
    }
  }
}

#endif /* _SK_OCI_DB_BIND_DATA_H_ */
