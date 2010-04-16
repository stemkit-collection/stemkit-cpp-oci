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
#include <sk/rt/Scope.h>

namespace sk {
  namespace oci {
    namespace bind {
      class in;
      class out;
    }
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

        sk::oci::Bind& operator<<(const sk::oci::Bind& other);
        sk::oci::bind::in operator<<(const sk::oci::bind::in& other);
        sk::oci::bind::out operator<<(const sk::oci::bind::out& other);

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      protected:
        const sk::rt::Scope& getScope() const;
    
      private:
        Bind& operator = (const Bind& other);
        sk::util::ArrayList<sk::oci::Bind> _binds;

        sk::rt::Scope _scope;
    };
  }
}

#endif /* _SK_OCI_BIND_H_ */
