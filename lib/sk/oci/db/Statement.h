/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_STATEMENT_H_
#define _SK_OCI_DB_STATEMENT_H_

#include <sk/oci/Statement.h>

#include "Handle.h"
#include "handle/Error.h"
#include "handle/Service.h"
#include "Binder.h"

namespace sk {
  namespace oci {
    class BindRegistry;

    namespace db {
      class Data;

      class Statement 
        : public db::Handle,
          public virtual sk::oci::Statement
      {
        public:
          Statement(db::handle::Error& error, const sk::util::String& sql);
          virtual ~Statement();

          void execute(db::handle::Service& service);

          // sk::oci::Statement implementation.
          bool isSelect() const;
          bool isUpdate() const;
          bool isDelete() const;
          bool isInsert() const;
          bool isCreate() const;
          bool isDrop() const;
          bool isAlter() const;
          bool isBegin() const;
          bool isDeclare() const;
          void setDescribeOnly(bool state);

          int bindStringAt(int position, int size, const sk::util::String& value);
          int bindIntAt(int position, uint32_t value);
          int bindStringTag(const sk::util::String& tag, int size, const sk::util::String& value);
          int bindIntTag(const sk::util::String& tag, uint32_t value);

          const sk::oci::BindRegistry& bindRegistry() const;
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
          // sk::oci::db::Handle override.
          OCIStmt* getHandle() const;

        private:
          Statement(const Statement& other);
          Statement& operator = (const Statement& other);

          int bindDataPosition(oci::db::Data& data);
          int bindDataTag(oci::db::Data& data);

          oci::db::Binder _binder;
          ub4 _mode;
          ub4 _type;
      };
    }
  }
}

#endif /* _SK_OCI_DB_STATEMENT_H_ */
