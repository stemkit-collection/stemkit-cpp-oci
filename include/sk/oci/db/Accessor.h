/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_ACCESSOR_H_
#define _SK_OCI_DB_ACCESSOR_H_

#include <sk/oci/Accessor.h>
#include <sk/util/String.h>
#include <sk/util/Holder.hxx>
#include <sk/rt/Scope.h>

namespace sk {
  namespace oci {
    namespace db {
      class Accessor 
        : public virtual sk::oci::Accessor
      {
        public:
          Accessor(const sk::util::String& username, const sk::util::String& password, const sk::util::String& database);
          virtual ~Accessor();
      
          // sk::oci::Accessor implementation.
          void close();
          void commit();
          void rollback();

          const sk::oci::info::Table describeTable(const sk::util::String& name);
          uint32_t tableSize(const sk::util::String& name);
          uint32_t execute(const sk::util::String& sql);
          uint32_t execute(const sk::util::String& sql, const sk::oci::Director& director);
          const sk::oci::bind::out execute(const sk::util::String& sql, const sk::oci::Bind& bind);

          const sk::util::String getConnectString() const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          Accessor(const Accessor& other);
          Accessor& operator = (const Accessor& other);

          void logon();
          void logoff();

          const sk::util::String _username;
          const sk::util::String _password;
          const sk::util::String _database;

          class Data;
          sk::util::Holder<Data> _dataHolder;
          Data& _data;
          sk::rt::Scope _scope;
          bool _connected;
      };
    }
  }
}

#endif /* _SK_OCI_DB_ACCESSOR_H_ */
