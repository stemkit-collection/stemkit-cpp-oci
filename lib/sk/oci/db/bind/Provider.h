/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_BIND_PROVIDER_H_
#define _SK_OCI_DB_BIND_PROVIDER_H_

#include <sk/util/Object.h>

namespace sk {
  namespace oci {
    namespace db {
      namespace bind {
        class Data;

        class Provider
          : public virtual sk::util::Object
        {
          public:
            virtual void bindDataPosition(db::bind::Data& data) = 0;
            virtual void bindDataTag(db::bind::Data& data) = 0;
            virtual uint32_t datasetSize() const = 0;
        };
      }
    }
  }
}

#endif /* _SK_OCI_DB_BIND_PROVIDER_H_ */
