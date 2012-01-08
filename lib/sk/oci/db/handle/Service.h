/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_HANDLE_SERVICE_H_
#define _SK_OCI_DB_HANDLE_SERVICE_H_

#include "Handle.h"
#include "handle/Error.h"
#include "handle/Server.h"
#include "handle/Session.h"

namespace sk {
  namespace oci {
    namespace db {
      namespace handle {
        class Service
          : public db::Handle
        {
          public:
            Service(db::handle::Error& error, db::handle::Session& session, db::handle::Server& server)
              : Handle(OCI_HTYPE_SVCCTX, error.environment(), error), _session(session), _server(server) {}

            void init() {
              db::Handle::init();

              setAttr(_server.getHandle(), 0, OCI_ATTR_SERVER);
              SK_OCI_ENSURE_SUCCESS(OCISessionBegin(getHandle(), error().getHandle(), _session.getHandle(), OCI_CRED_RDBMS, OCI_DEFAULT));
              setAttr(_session.getHandle(), 0, OCI_ATTR_SESSION);
            }

            void commit() {
              SK_OCI_ENSURE_SUCCESS(OCITransCommit(getHandle(), error().getHandle(), OCI_DEFAULT));
            }

            void rollback() {
              SK_OCI_ENSURE_SUCCESS(OCITransRollback(getHandle(), error().getHandle(), OCI_DEFAULT));
            }

            void reset() {
              if(haveHandle() == false) {
                return;
              }
              try {
                SK_OCI_ENSURE_SUCCESS(OCISessionEnd(getHandle(), error().getHandle(), _session.getHandle(), OCI_DEFAULT));
              }
              catch(...) {
                db::Handle::reset();
                throw;
              }
              db::Handle::reset();
            }

            OCISvcCtx* getHandle() const {
              return reinterpret_cast<OCISvcCtx*>(db::Handle::getHandle());
            }

          private:
            Service(const Service& other);
            Service& operator = (const Service& other);

            db::handle::Session& _session;
            db::handle::Server& _server;
        };
      }
    }
  }
}

#endif /* _SK_OCI_DB_HANDLE_SERVICE_H_ */
