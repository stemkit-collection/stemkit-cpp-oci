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

namespace sk {
  namespace oci {
    namespace info {
      class Table 
        : public virtual sk::util::Object
      {
        public:
          Table();
          virtual ~Table();
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          Table(const Table& other);
          Table& operator = (const Table& other);
      };
    }
  }
}

#endif /* _SK_OCI_INFO_TABLE_H_ */
