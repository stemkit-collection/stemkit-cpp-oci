/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_ERROREXCEPTION_H_
#define _SK_OCI_ERROREXCEPTION_H_

#include <sk/oci/Exception.h>

namespace sk {
  namespace oci {
    class ErrorException 
      : public sk::oci::Exception
    {
      public:
        ErrorException(const sk::util::String& origin, int code, const sk::util::String& message);

        int getCode() const;
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        int _code;
    };
  }
}

#endif /* _SK_OCI_ERROREXCEPTION_H_ */
