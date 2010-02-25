/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_BIND_REGISTRY_H_
#define _SK_OCI_DB_BIND_REGISTRY_H_

#include <sk/oci/BindRegistry.h>

namespace sk {
  namespace oci {
    namespace db {
        class Data;

      namespace bind {
        class Registry 
          : public virtual sk::oci::BindRegistry
        {
          public:
            Registry();
            virtual ~Registry();

            db::Data& bindString(int position, int sze, const sk::util::String& value);
            db::Data& bindInteger(int position, uint32_t value);
            db::Data& bindString(const sk::util::String& tag, int sze, const sk::util::String& value);
            db::Data& bindInteger(const sk::util::String& tag, uint32_t value);

            const sk::oci::Data& boundDataAt(int index) const;
        
            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;
        
          private:
            Registry(const Registry& other);
            Registry& operator = (const Registry& other);
        };
      }
    }
  }
}

#endif /* _SK_OCI_DB_BIND_REGISTRY_H_ */
