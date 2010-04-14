/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_BIND_DATA_H_
#define _SK_OCI_BIND_DATA_H_

#include <sk/util/Object.h>

namespace sk {
  namespace oci {
    namespace bind {
      class Data 
        : public virtual sk::util::Object
      {
        public:
          Data();
          virtual ~Data();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          Data& operator = (const Data& other);
      };
    }
  }
}

#endif /* _SK_OCI_BIND_DATA_H_ */
