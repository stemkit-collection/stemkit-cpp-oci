/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_BIND_INTEGERVALUE_H_
#define _SK_OCI_BIND_INTEGERVALUE_H_

#include <sk/util/Object.h>
#include <sk/util/Integers.h>
#include "Value.h"

namespace sk {
  namespace oci {
    namespace bind {
      class IntegerValue 
        : public bind::Value
      {
        public:
          IntegerValue(const sk::util::Integers& data);
          virtual ~IntegerValue();
      
          // sk::oci::bind::Value implementation.
          void bindTag(const sk::util::String& tag, sk::oci::Statement& statement) const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          IntegerValue(const IntegerValue& other);
          IntegerValue& operator = (const IntegerValue& other);

          const sk::util::Integers _data;
      };
    }
  }
}

#endif /* _SK_OCI_BIND_INTEGERVALUE_H_ */
