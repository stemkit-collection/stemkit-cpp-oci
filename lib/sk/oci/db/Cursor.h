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
#include "Statement.h"

namespace sk {
  namespace oci {
    namespace db {
      class Cursor 
        : public virtual sk::oci::Cursor
      {
        public:
          Cursor(db::Statement& statement);
          virtual ~Cursor();

          uint64_t rowCount();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          Cursor(const Cursor& other);
          Cursor& operator = (const Cursor& other);

          db::Statement& _statement;
      };
    }
  }
}

#endif /* _SK_OCI_DB_CURSOR_H_ */
