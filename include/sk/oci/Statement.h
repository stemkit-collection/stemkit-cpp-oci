/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_STATEMENT_H_
#define _SK_OCI_STATEMENT_H_

#include <sk/util/Object.h>

namespace sk {
  namespace oci {
    class Statement 
      : public virtual sk::util::Object
    {
      public:
        Statement();
        virtual ~Statement();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        Statement(const Statement& other);
        Statement& operator = (const Statement& other);
    };
  }
}

#endif /* _SK_OCI_STATEMENT_H_ */
