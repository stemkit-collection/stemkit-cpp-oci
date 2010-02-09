/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_OCI_LOGONEXCEPTION_H_
#define _SK_OCI_LOGONEXCEPTION_H_

#include <sk/oci/Exception.h>

namespace sk {
  namespace oci {
    class LogonException 
      : public sk::oci::Exception
    {
      public:
        LogonException(const sk::util::String& connectString, const sk::util::String& message);
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_OCI_LOGONEXCEPTION_H_ */
