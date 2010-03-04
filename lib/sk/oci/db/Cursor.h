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
          bool hasInfo() const;
          void setCapacity(uint32_t capacity);
          void useTruncate(bool state);
          void useColumnCodes(bool state);

          // sk::oci::OutputPositionBind implementation.
          int bindIntAt(int position);
          int bindCharsAt(int position, int size);

          // sk::oci::BindRegistry implementation.
          const sk::oci::Data& boundData(int bid) const;
          sk::oci::Data& boundMutableData(int bid);

        private:
          Cursor(const Cursor& other);
          Cursor& operator = (const Cursor& other);

          uint32_t updateRowcount();

          // sk::oci::db::bind::Provider implementation.
          void bindDataPosition(db::bind::Data& data);
          void bindDataTag(db::bind::Data& data);
          uint32_t datasetSize() const;

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
