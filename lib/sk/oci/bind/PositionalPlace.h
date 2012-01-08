/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_BIND_POSITIONALPLACE_H_
#define _SK_OCI_BIND_POSITIONALPLACE_H_

#include <sk/util/Object.h>
#include "Place.h"

namespace sk {
  namespace oci {
    namespace bind {
      class PositionalPlace
        : public bind::Place
      {
        public:
          PositionalPlace(int position);
          virtual ~PositionalPlace();

          // sk::oci::bin::Place implementation.
          void bind(sk::oci::Statement& statement) const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        private:
          PositionalPlace(const PositionalPlace& other);
          PositionalPlace& operator = (const PositionalPlace& other);

          const int _position;
      };
    }
  }
}

#endif /* _SK_OCI_BIND_POSITIONALPLACE_H_ */
