/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_BIND_STRINGDATA_H_
#define _SK_OCI_DB_BIND_STRINGDATA_H_

#include "Data.h"

namespace sk {
  namespace oci {
    namespace db {
      namespace bind {
        class StringData 
          : public bind::Data
        {
          public:
            StringData(uint32_t position, int size, const sk::util::String& value);
            virtual ~StringData();
        
            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;
            const sk::util::String inspect() const;
        
          private:
            StringData(const StringData& other);
            StringData& operator = (const StringData& other);
        };
      }
    }
  }
}

#endif /* _SK_OCI_DB_BIND_STRINGDATA_H_ */
