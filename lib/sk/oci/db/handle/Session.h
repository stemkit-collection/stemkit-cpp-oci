/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_HANDLE_SESSION_H_
#define _SK_OCI_DB_HANDLE_SESSION_H_

#include "Handle.h"

namespace sk {
  namespace oci {
    namespace db {
      namespace handle {
        class Session
          : public db::Handle
        {
          public:
            Session(db::Environment& env, db::handle::Error& error)
              : Handle(OCI_HTYPE_SESSION, env, error) {}

            void init(const sk::util::String& username, const sk::util::String& password) {
              db::Handle::init();
              setAttr(username.getChars(), username.length(), OCI_ATTR_USERNAME);
              setAttr(password.getChars(), password.length(), OCI_ATTR_PASSWORD);
            }

            OCISession* getHandle() const {
              return reinterpret_cast<OCISession*>(db::Handle::getHandle());
            }

          private:
            Session(const Session& other);
            Session& operator = (const Session& other);
        };
      }
    }
  }
}

#endif /* _SK_OCI_DB_HANDLE_SESSION_H_ */
