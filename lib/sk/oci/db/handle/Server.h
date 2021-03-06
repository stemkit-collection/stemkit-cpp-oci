/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_HANDLE_SERVER_H_
#define _SK_OCI_DB_HANDLE_SERVER_H_

#include "Handle.h"

namespace sk {
  namespace oci {
    namespace db {
      namespace handle {
        class Server
          : public db::Handle
        {
          public:
            Server(db::Environment& env, db::handle::Error& error)
              : Handle(OCI_HTYPE_SERVER, env, error) {}

            void init(const sk::util::String database) {
              db::Handle::init();
              SK_OCI_ENSURE_SUCCESS(OCIServerAttach(getHandle(), error().getHandle(), toOraText(database), database.length(), OCI_DEFAULT));
            }

            void reset() {
              if(haveHandle() == false) {
                return;
              }
              try {
                SK_OCI_ENSURE_SUCCESS(OCIServerDetach(getHandle(), error().getHandle(), OCI_DEFAULT));
              }
              catch(...) {
                db::Handle::reset();
                throw;
              }
              db::Handle::reset();
            }

            OCIServer* getHandle() const {
              return reinterpret_cast<OCIServer*>(db::Handle::getHandle());
            }

          private:
            Server(const Server& other);
            Server& operator = (const Server& other);
        };
      }
    }
  }
}

#endif /* _SK_OCI_DB_HANDLE_SERVER_H_ */
