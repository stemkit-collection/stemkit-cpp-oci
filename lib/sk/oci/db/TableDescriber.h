/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_TABLEDESCRIBER_H_
#define _SK_OCI_DB_TABLEDESCRIBER_H_

#include <sk/oci/info/Table.h>
#include <sk/oci/info/Column.h>
#include <sk/oci/Director.h>
#include <sk/util/Processor.h>

namespace sk {
  namespace oci {
    namespace db {
      class TableDescriber 
        : public virtual sk::oci::Director,
          public virtual sk::util::Processor<const info::Column> 
      {
        public:
          TableDescriber(sk::oci::info::Table& table);
          TableDescriber(const TableDescriber& other);
          virtual ~TableDescriber();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
          // sk::oci::Director implementation.
          void prepareStatement(sk::oci::Statement& statement) const;
          void processCursor(sk::oci::Cursor& cursor) const;

          // sk::util::Processor implementation.
          void process(const info::Column& column) const;
      
        private:
          TableDescriber& operator = (const TableDescriber& other);

          info::Table& _table;
      };
    }
  }
}

#endif /* _SK_OCI_DB_TABLEDESCRIBER_H_ */
