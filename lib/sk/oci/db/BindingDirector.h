/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_BINDINGDIRECTOR_H_
#define _SK_OCI_DB_BINDINGDIRECTOR_H_

#include <sk/oci/Director.h>
#include <sk/oci/Bind.h>
#include <sk/oci/bind/Data.h>

namespace sk {
  namespace oci {
    namespace db {
      class BindingDirector 
        : public virtual sk::oci::Director
      {
        public:
          BindingDirector(const sk::oci::Bind& bind);
          virtual ~BindingDirector();

          const sk::oci::bind::Data& data() const;

          // sk::oci::Director implementation.
          void prepareStatement(sk::oci::Statement& statement) const;
          void processCursor(sk::oci::Cursor& cursor) const;
          bool nextIteration() const;
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          BindingDirector(const BindingDirector& other);
          BindingDirector& operator = (const BindingDirector& other);

          const sk::oci::Bind& _bind;
          mutable sk::oci::bind::Data _data;
      };
    }
  }
}

#endif /* _SK_OCI_DB_BINDINGDIRECTOR_H_ */
