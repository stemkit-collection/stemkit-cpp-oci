/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_HANDLE_PARAMETER_H_
#define _SK_OCI_DB_HANDLE_PARAMETER_H_

#include "Handle.h"
#include "Statement.h"

namespace sk {
  namespace oci {
    namespace db {
      namespace handle {
        class Parameter
          : public db::Handle
        {
          public:
            Parameter(db::Statement& statement, int index)
              : Handle(OCI_DTYPE_PARAM, statement.environment(), statement.error())
            {
              void* handle = 0;
              SK_OCI_ENSURE_SUCCESS(OCIParamGet(statement.getHandle(), statement.type(), error().getHandle(), &handle, index));
              init(handle);
            }

            void reset() {
            }

          private:
            Parameter(const Parameter& other);
            Parameter& operator = (const Parameter& other);
        };
      }
    }
  }
}

#endif /* _SK_OCI_DB_HANDLE_PARAMETER_H_ */
