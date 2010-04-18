/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_BIND_TAGGEDPLACE_H_
#define _SK_OCI_BIND_TAGGEDPLACE_H_

#include <sk/util/Object.h>
#include "Place.h"

namespace sk {
  namespace oci {
    namespace bind {
      class TaggedPlace 
        : public bind::Place
      {
        public:
          TaggedPlace(const sk::util::String& tag);
          virtual ~TaggedPlace();

          // sk::oci::bin::Place implementation.
          void bind(sk::oci::Statement& statement) const;
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        private:
          TaggedPlace(const TaggedPlace& other);
          TaggedPlace& operator = (const TaggedPlace& other);

          const sk::util::String _tag;
      };
    }
  }
}

#endif /* _SK_OCI_BIND_TAGGEDPLACE_H_ */
