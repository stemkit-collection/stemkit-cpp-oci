/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_VALUE_H_
#define _SK_OCI_VALUE_H_

#include <sk/util/Object.h>

namespace sk {
  namespace oci {
    class Statement;

    class Value 
      : public virtual sk::util::Object
    {
      public:
        virtual void bindTag(const sk::util::String& tag, sk::oci::Statement& statement) const = 0;
        virtual void bindPosition(int position, sk::oci::Statement& statement) const = 0;
    };
  }
}

#endif /* _SK_OCI_VALUE_H_ */
