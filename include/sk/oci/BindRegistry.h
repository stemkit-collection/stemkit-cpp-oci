/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_BINDREGISTRY_H_
#define _SK_OCI_BINDREGISTRY_H_

#include <sk/util/Object.h>

namespace sk {
  namespace oci {
    class Data;

    class BindRegistry
      : public virtual sk::util::Object
    {
      public:
        virtual void setCapacity(uint32_t number) = 0;
        virtual const sk::oci::Data& boundData(int bid) const = 0;
        virtual sk::oci::Data& boundMutableData(int bid) = 0;
    };
  }
}

#endif /* _SK_OCI_BINDREGISTRY_H_ */
