/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_CURSOR_H_
#define _SK_OCI_DB_CURSOR_H_

#include <sk/oci/Cursor.h>
#include <sk/oci/BindRegistry.h>
#include "Statement.h"
#include "bind/Provider.h"

namespace sk {
  namespace oci {
    namespace db {
      class Cursor 
        : public virtual sk::oci::Cursor,
          public virtual sk::oci::BindRegistry,
          public virtual bind::Provider

      {
        public:
          Cursor(db::Statement& statement);
          virtual ~Cursor();

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

          // sk::oci::Cursor implementation.
          uint32_t rowCount();
          uint32_t columnCount();
          const info::Column columnAt(int index);
          void forEachColumn(const sk::util::Processor<const info::Column>& processor);
          uint32_t fetch();
          void setCapacity(uint32_t capacity);

          // sk::oci::OutputPositionBind implementation.
          int bindIntAt(int position);
          int bindStringAt(int position, int size);

          // sk::oci::BindRegistry implementation.
          const sk::oci::Data& boundDataAt(int index) const;

        private:
          Cursor(const Cursor& other);
          Cursor& operator = (const Cursor& other);

          // sk::oci::db::bind::Provider implementation.
          void bindDataPosition(oci::db::Data& data);
          void bindDataTag(oci::db::Data& data);

          db::Statement& _statement;
          bool _haveColumnCount;
          uint32_t _columnCount;
          uint32_t _rowCount;
          uint32_t _capacity;
      };
    }
  }
}

#endif /* _SK_OCI_DB_CURSOR_H_ */
