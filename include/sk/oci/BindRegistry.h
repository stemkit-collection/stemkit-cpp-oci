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
        virtual const sk::oci::Data& boundDataAt(int index) const = 0;
    };
  }
}

#endif /* _SK_OCI_BINDREGISTRY_H_ */
