/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_DATA_INTEGER_H_
#define _SK_OCI_DB_DATA_INTEGER_H_

#include <sk/util/Object.h>

namespace sk {
  namespace oci {
    namespace db {
      namespace data {
        class Integer 
          : public virtual sk::util::Object
        {
          public:
            Integer();
            virtual ~Integer();
        
            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;
        
          private:
            Integer(const Integer& other);
            Integer& operator = (const Integer& other);
        };
      }
    }
  }
}

#endif /* _SK_OCI_DB_DATA_INTEGER_H_ */
