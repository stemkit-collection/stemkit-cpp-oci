/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_INFO_TABLE_H_
#define _SK_OCI_INFO_TABLE_H_

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <sk/oci/info/Column.h>

namespace sk {
  namespace oci {
    namespace info {
      class Table 
        : public virtual sk::util::Object
      {
        public:
          Table(const sk::util::String& name);
          Table(const Table& other);
          virtual ~Table();

          void add(const info::Column& column);
          const sk::util::String getName() const;
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        private:
          Table& operator = (const Table& other);

          const sk::util::String _name;
      };
    }
  }
}

#endif /* _SK_OCI_INFO_TABLE_H_ */
