/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_ACCESSOR_H_
#define _SK_OCI_DB_ACCESSOR_H_

#include <sk/oci/Accessor.h>

namespace sk {
  namespace oci {
    namespace db {
      class Accessor 
        : public virtual sk::oci::Accessor
      {
        public:
          Accessor();
          virtual ~Accessor();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          Accessor(const Accessor& other);
          Accessor& operator = (const Accessor& other);
      };
    }
  }
}

#endif /* _SK_OCI_DB_ACCESSOR_H_ */
