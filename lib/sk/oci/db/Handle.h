/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_HANDLE_H_
#define _SK_OCI_DB_HANDLE_H_

#include <sk/util/String.h>
#include <oci.h>
#include <vector>

namespace sk {
  namespace oci {
    namespace db {
      namespace handle {
        class Error;
      }
      class Environment;

      class Handle 
      {
        public:
          Handle(ub4 type, db::Environment& env, db::handle::Error& error);
          ~Handle();

          void init();
          void reset();

          void* getHandle() const;
          db::handle::Error& error() const;

          void setAttr(const void* attr, ub4 size, ub4 attrType);
          const OraText* toOraText(const sk::util::String& string) const;
          OraText* toOraText(std::vector<char> buffer) const;

          void ensureSuccess(int status, const char* expression) const;

        private:
          Handle(const Handle& other);
          Handle& operator = (const Handle& other);

          void* _handle;
          ub4 _type;
          db::Environment& _env;
          db::handle::Error& _error;
      };
    }
  }
}

#define SK_OCI_ENSURE_SUCCESS(expression) ensureSuccess((expression), #expression)

#endif /* _SK_OCI_DB_HANDLE_H_ */
