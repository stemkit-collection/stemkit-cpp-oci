/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DIRECTOR_H_
#define _SK_OCI_DIRECTOR_H_

#include <sk/util/Object.h>
#include <sk/oci/Statement.h>
#include <sk/oci/Cursor.h>

namespace sk {
  namespace oci {
    class Director 
      : public virtual sk::util::Object
    {
      public:
        virtual void prepareStatement(sk::oci::Statement& statement) const = 0;
        virtual void processCursor(sk::oci::Cursor& cursor) const = 0;
    };
  }
}

#endif /* _SK_OCI_DIRECTOR_H_ */
