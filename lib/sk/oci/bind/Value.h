/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_BIND_VALUE_H_
#define _SK_OCI_BIND_VALUE_H_

#include <sk/util/Object.h>

namespace sk {
  namespace oci {
    class Statement;

    namespace bind {
      class Value 
        : public virtual sk::util::Object
      {
        public:
          Value();
          virtual ~Value();

          virtual void bindTag(const sk::util::String& tag, sk::oci::Statement& statement) const = 0;
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          Value(const Value& other);
          Value& operator = (const Value& other);
      };
    }
  }
}

#endif /* _SK_OCI_BIND_VALUE_H_ */
