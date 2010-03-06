/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_BIND_CHARSDATA_H_
#define _SK_OCI_DB_BIND_CHARSDATA_H_

#include "Data.h"
#include <sk/util/Strings.h>

namespace sk {
  namespace oci {
    namespace db {
      namespace bind {
        class CharsData 
          : public bind::Data
        {
          public:
            CharsData(int capacity, const sk::util::String& tag, int size, const sk::util::Strings& values);
            CharsData(int capacity, const sk::util::String& tag, int size);
            CharsData(int capacity, uint32_t position, int size, const sk::util::Strings& values);
            CharsData(int capacity, uint32_t position, int size);
            virtual ~CharsData();
        
            // sk::oci::db::bind::Data implementation.
            const sk::util::String toString(int index) const;
            const sk::util::String inspect(int index) const;

            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;
        
          private:
            CharsData(const CharsData& other);
            CharsData& operator = (const CharsData& other);

            void setValues(const sk::util::Strings& values);
        };
      }
    }
  }
}

#endif /* _SK_OCI_DB_BIND_CHARSDATA_H_ */
