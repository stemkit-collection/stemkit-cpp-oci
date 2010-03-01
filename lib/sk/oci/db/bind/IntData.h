/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_BIND_INTDATA_H_
#define _SK_OCI_DB_BIND_INTDATA_H_

#include "Data.h"

namespace sk {
  namespace oci {
    namespace db {
      namespace bind {
        class IntData 
          : public bind::Data
        {
          public:
            IntData(int capacity, uint32_t position, uint32_t value);
            IntData(int capacity, uint32_t position);
        
            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;
            const sk::util::String toString() const;
            const sk::util::String inspect() const;
        
          private:
            IntData(const IntData& other);
            IntData& operator = (const IntData& other);
        };
      }
    }
  }
}

#endif /* _SK_OCI_DB_BIND_INTDATA_H_ */
