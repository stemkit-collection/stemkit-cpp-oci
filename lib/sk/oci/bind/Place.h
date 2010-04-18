/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_BIND_PLACE_H_
#define _SK_OCI_BIND_PLACE_H_

#include <sk/util/Object.h>
#include <sk/util/Holder.hxx>
#include "Value.h"

namespace sk {
  namespace oci {
    class Statement;

    namespace bind {
      class Place 
        : public virtual sk::util::Object
      {
        public:
          Place();
          virtual ~Place();

          void setValue(bind::Value* value);
          const bind::Value& getValue() const;

          virtual void bind(sk::oci::Statement& statement) const = 0;
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          Place(const Place& other);
          Place& operator = (const Place& other);

          sk::util::Holder<bind::Value> _valueHolder;
      };
    }
  }
}

#endif /* _SK_OCI_BIND_PLACE_H_ */
