/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_BIND_IN_H_
#define _SK_OCI_BIND_IN_H_

#include <sk/util/Object.h>
#include <sk/oci/Bind.h>

namespace sk {
  namespace oci {
    namespace bind {
      class in 
        : public sk::oci::Bind
      {
        public:
          in();
          in(const in& other);
          virtual ~in();
      
          // sk::oci::Bind implementation.
          void prepareStatement(sk::oci::Statement& statement) const;
          void processCursor(sk::oci::Cursor& cursor, sk::oci::bind::Data& data) const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          in& operator = (const in& other);
      };
    }
  }
}

#endif /* _SK_OCI_BIND_IN_H_ */
