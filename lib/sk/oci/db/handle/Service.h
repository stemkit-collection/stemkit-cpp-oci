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

namespace sk {
  namespace oci {
    namespace db {
      namespace handle {
        class Service 
          : public db::Handle
        {
          public:
            Service(db::Environment& env, db::handle::Session& session, db::handle::Server& server, db::handle::Error& error)
              : Handle(OCI_HTYPE_SVCCTX, env, error), _session(session), _server(server) {}

            void init() {
              db::Handle::init();

              setAttr(_server.getHandle(), 0, OCI_ATTR_SERVER);
              SK_OCI_ENSURE_SUCCESS(OCISessionBegin(getHandle(), error().getHandle(), _session.getHandle(), OCI_CRED_RDBMS, OCI_DEFAULT));
              setAttr(_session.getHandle(), 0, OCI_ATTR_SESSION);
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
