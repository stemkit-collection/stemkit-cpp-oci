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
#include "bind/Registry.h"
#include "bind/Provider.h"

namespace sk {
  namespace oci {
    class BindRegistry;

    namespace db {
      class Statement 
        : public db::Handle,
          public virtual oci::Statement,
          public virtual oci::db::bind::Provider
      {
        public:
          Statement(db::handle::Error& error, const sk::util::String& sql);
          virtual ~Statement();

          void execute(db::handle::Service& service);
          void fetch(uint32_t amount);
          uint32_t obtainRowCount();
          db::bind::Registry& bindRegistry();
          void defineDataPosition(db::bind::Data& data);

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

          // sk::oci::Statement implementation.
          void setDescribeOnly(bool state);
          void setIterations(uint32_t number);
          void setRowOffset(uint32_t offset);

          // sk::oci::Statement implementation.
          void useTruncate(bool state);
          void useColumnLevelCodes(bool state);

          // sk::oci::InputPositionBinder implementation.
          int bindStringAt(int position, int size, const sk::util::String& value);
          int bindIntAt(int position, uint32_t value);

          // sk::oci::InputTagBinder implementation.
          int bindStringTag(const sk::util::String& tag, int size, const sk::util::String& value);
          int bindIntTag(const sk::util::String& tag, uint32_t value);

          // sk::oci::BindRegistry implementation.
          const sk::oci::Data& boundDataAt(int index) const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
          // sk::oci::db::Handle override.
          OCIStmt* getHandle() const;

        private:
          Statement(const Statement& other);
          Statement& operator = (const Statement& other);

          // sk::db::Handle re-implementation.
          sb4 mapOracleError(sb4 code) const;

          // sk::oci::db::bind::Provider implementation.
          void bindDataPosition(db::bind::Data& data);
          void bindDataTag(db::bind::Data& data);
          uint32_t datasetSize() const;

          db::bind::Registry _bindRegistry;
          ub4 _mode;
          ub4 _type;
          ub4 _iterations;
          ub4 _offset;

          bool _useColumnLevelCodes;
          bool _useTruncate;
      };
    }
  }
}

#endif /* _SK_OCI_DB_STATEMENT_H_ */
