/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_HANDLE_ERROR_H_
#define _SK_OCI_DB_HANDLE_ERROR_H_

#include <sk/oci/Exception.h>
#include <sk/rt/Scope.h>

#include "Handle.h"
#include <vector>

namespace sk {
  namespace oci {
    namespace db {
      class Environment;
      namespace handle {
        class Error
          : public db::Handle
        {
          public:
            Error(db::Environment& env)
              : Handle(OCI_HTYPE_ERROR, env, *this), _scope("OCI") {}

            OCIError* getHandle() const {
              return reinterpret_cast<OCIError*>(db::Handle::getHandle());
            }

            sb4 getError(std::vector<char>& buffer) {
              sb4 errorcode;
              sword status = OCIErrorGet(getHandle(), 1, 0, &errorcode, toOraText(buffer), buffer.size(), OCI_HTYPE_ERROR);
              if(status != OCI_SUCCESS) {
                throw sk::oci::Exception("OCIErrorGet", "Cannot get OCI error code, status=" + sk::util::String::valueOf(status));
              }
              return errorcode;
            }

            void handleSuccessWithInfo(const sk::util::String& origin) const {
              _scope.warning("SUCCESS_WITH_INFO") << origin;
            }

          private:
            Error(const Error& other);
            Error& operator = (const Error& other);

            sk::rt::Scope _scope;
        };
      }
    }
  }
}

#endif /* _SK_OCI_DB_HANDLE_ERROR_H_ */
