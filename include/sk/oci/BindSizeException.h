/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_BINDSIZEEXCEPTION_H_
#define _SK_OCI_BINDSIZEEXCEPTION_H_

#include <sk/oci/Exception.h>

namespace sk {
  namespace oci {
    class BindSizeException 
      : public virtual sk::oci::Exception
    {
      public:
        BindSizeException(const sk::util::String& origin, uint32_t expected, uint32_t actual);

        uint32_t getExpected() const;
        uint32_t getActual() const;
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        uint32_t _expected;
        uint32_t _actual;
    };
  }
}

#endif /* _SK_OCI_BINDSIZEEXCEPTION_H_ */
