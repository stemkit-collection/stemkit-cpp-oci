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
#include <sk/util/Integers.h>
#include <sk/util/Strings.h>

namespace sk {
  namespace oci {
    namespace bind {
      class Data
        : public virtual sk::util::Object
      {
        public:
          Data();
          virtual ~Data();

          const sk::util::String& string(int position = 1) const;
          uint32_t integer(int position = 1) const;

          const sk::util::Integers& integers(int position = 1) const;
          const sk::util::Strings& strings(int position = 1) const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        private:
          Data& operator = (const Data& other);
      };
    }
  }
}

#endif /* _SK_OCI_BIND_DATA_H_ */
