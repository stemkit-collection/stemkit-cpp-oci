/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_EXCEPTION_H_
#define _SK_OCI_EXCEPTION_H_

#include <sk/util/Exception.h>

namespace sk {
  namespace oci {
    class Exception 
      : public sk::util::Exception
    {
      public:
        Exception(const sk::util::String& origin, const sk::util::String& message);

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
    };
  }
}

#endif /* _SK_OCI_EXCEPTION_H_ */
