/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_BIND_STRINGVALUE_H_
#define _SK_OCI_BIND_STRINGVALUE_H_

#include <sk/util/Object.h>
#include <sk/util/Strings.h>
#include "Value.h"

namespace sk {
  namespace oci {
    namespace bind {
      class StringValue 
        : public bind::Value
      {
        public:
          StringValue(const sk::util::Strings& data);
          virtual ~StringValue();
      
          // sk::oci::bind::Value implementation.
          void bindTag(const sk::util::String& tag, sk::oci::Statement& statement) const;
          void bindPosition(int position, sk::oci::Statement& statement) const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          StringValue(const StringValue& other);
          StringValue& operator = (const StringValue& other);

          int maxDataItem() const;
          
          const sk::util::Strings _data;
      };
    }
  }
}

#endif /* _SK_OCI_BIND_STRINGVALUE_H_ */
