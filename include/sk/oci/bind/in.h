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

namespace sk {
  namespace oci {
    namespace bind {
      class in 
        : public virtual sk::util::Object
      {
        public:
          in();
          virtual ~in();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          in(const in& other);
          in& operator = (const in& other);
      };
    }
  }
}

#endif /* _SK_OCI_BIND_IN_H_ */
