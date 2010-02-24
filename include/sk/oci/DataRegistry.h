/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DATAREGISTRY_H_
#define _SK_OCI_DATAREGISTRY_H_

#include <sk/util/Object.h>
#include <sk/oci/Data.h>

namespace sk {
  namespace oci {
    class DataRegistry 
      : public virtual sk::util::Object
    {
      public:
        virtual const sk::oci::Data& at(int position) const = 0;
        virtual const sk::oci::Data& tagged(int position) const = 0;
        virtual const sk::oci::Data& tagged(const sk::util::String& tag) const = 0;
    };
  }
}

#endif /* _SK_OCI_DATAREGISTRY_H_ */
