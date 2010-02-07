/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_ACCESSOR_H_
#define _SK_OCI_ACCESSOR_H_

#include <sk/util/Object.h>
#include <sk/oci/Director.h>
#include <sk/oci/info/Table.h>

namespace sk {
  namespace oci {
    class Accessor 
      : public virtual sk::util::Object
    {
      public:
        virtual void close() = 0;
        virtual void commit() = 0;
        virtual void rollback() = 0;

        virtual const sk::oci::info::Table describe(const sk::util::String& name) = 0;
        virtual uint64_t execute(const sk::util::String& statement) = 0;
        virtual uint64_t execute(const sk::util::String& statement, const sk::oci::Director& director) = 0;
    };
  }
}

#endif /* _SK_OCI_ACCESSOR_H_ */
