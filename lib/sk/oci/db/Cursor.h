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

namespace sk {
  namespace oci {
    namespace db {
      class Cursor 
        : public virtual sk::oci::Cursor,
          public virtual sk::oci::BindRegistry
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
          int bindIntAt(int position);

          // sk::oci::BindRegistry implementation (via sk::oci::Cursor).
          const sk::oci::Data& boundDataAt(int index) const;

        private:
          Cursor(const Cursor& other);
          Cursor& operator = (const Cursor& other);

          db::Statement& _statement;
          bool _haveColumnCount;
          uint32_t _columnCount;
      };
    }
  }
}

#endif /* _SK_OCI_DB_CURSOR_H_ */
