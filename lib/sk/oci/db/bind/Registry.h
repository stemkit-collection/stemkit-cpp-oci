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

#include <sk/util/ArrayList.hxx>
#include <sk/oci/BindRegistry.h>
#include "Provider.h"

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

            int bindString(db::bind::Provider& provider, int position, int sze, const sk::util::String& value);
            int bindInteger(db::bind::Provider& provider, int position, uint32_t value);
            int bindString(db::bind::Provider& provider, const sk::util::String& tag, int sze, const sk::util::String& value);
            int bindInteger(db::bind::Provider& provider, const sk::util::String& tag, uint32_t value);

            const sk::oci::Data& boundDataAt(int index) const;
        
            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;
        
          private:
            Registry(const Registry& other);
            Registry& operator = (const Registry& other);

            sk::util::ArrayList<db::Data> _depot;
        };
      }
    }
  }
}

#endif /* _SK_OCI_DB_BIND_REGISTRY_H_ */
