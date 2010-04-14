/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_BIND_H_
#define _SK_OCI_BIND_H_

#include <sk/util/Object.h>
#include <sk/oci/bind/Data.h>
#include <sk/oci/Statement.h>
#include <sk/oci/Cursor.h>
#include <sk/util/ArrayList.hxx>

namespace sk {
  namespace oci {
    class Bind 
      : public virtual sk::util::Object
    {
      public:
        Bind();
        Bind(const Bind& other);
        virtual ~Bind();

        void accept(sk::oci::Statement& statement) const;
        void accept(sk::oci::Cursor& cursor, sk::oci::bind::Data& data) const;

        virtual void prepareStatement(sk::oci::Statement& statement) const;
        virtual void processCursor(sk::oci::Cursor& cursor, sk::oci::bind::Data& data) const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        Bind& operator = (const Bind& other);
        sk::util::ArrayList<sk::oci::Bind> _binds;
    };
  }
}

#endif /* _SK_OCI_BIND_H_ */
