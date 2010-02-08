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

#include "Handle.h"
#include <sk/util/IllegalStateException.h>
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
              : Handle(OCI_HTYPE_ERROR, env, *this) {}

            OCIError* getHandle() const {
              return reinterpret_cast<OCIError*>(db::Handle::getHandle());
            }

            sb4 getError(int status, std::vector<char> buffer) {
              sb4 errorcode;
              if(OCI_SUCCESS != OCIErrorGet(getHandle(), 1, 0, &errorcode, reinterpret_cast<OraText*>(&buffer.front()), buffer.size(), OCI_HTYPE_ERROR)) {
                throw sk::util::IllegalStateException("OCIErrorGet failed");
              }
              return errorcode;
            }

          private:
            Error(const Error& other);
            Error& operator = (const Error& other);
        };
      }
    }
  }
}

#endif /* _SK_OCI_DB_HANDLE_ERROR_H_ */
