/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_BIND_OUT_H_
#define _SK_OCI_BIND_OUT_H_

#include <sk/util/Object.h>
#include <sk/oci/Integers.h>
#include <sk/oci/Strings.h>
#include <sk/oci/Bind.h>

namespace sk {
  namespace oci {
    namespace bind {
      class out 
        : public sk::oci::Bind
      {
        public:
          out();
          out(uint32_t amount);
          out(uint32_t amount, uint32_t skip);
          virtual ~out();
      
          sk::oci::bind::out& operator<<(const sk::oci::Integers& values);
          sk::oci::bind::out& operator<<(const sk::oci::Strings& values);

          using sk::oci::Bind::operator<<;

          // sk::oci::Bind implementation.
          void prepareStatement(sk::oci::Statement& statement) const;
          void processCursor(sk::oci::Cursor& cursor, sk::oci::bind::Data& data) const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          out& operator = (const out& other);
          const uint32_t _amount;
          const uint32_t _skip;
      };
    }
  }
}

#endif /* _SK_OCI_BIND_OUT_H_ */
