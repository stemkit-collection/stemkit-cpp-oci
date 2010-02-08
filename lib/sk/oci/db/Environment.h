/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_ENVIRONMENT_H_
#define _SK_OCI_DB_ENVIRONMENT_H_

#include <sk/oci/Exception.h>

namespace sk {
  namespace oci {
    namespace db {
      class Environment 
      {
        public:
          Environment() 
            : _handle(0) {}

          ~Environment() {
            reset();
          }

          void init(ub4 mode) {
            if(OCI_SUCCESS != OCIEnvCreate(&_handle, mode, 0, 0, 0, 0, 0, 0)) {
              throw sk::oci::Exception("OCIEnvCreate", "Cannot create OCI environment");
            }
          }

          void reset() {
            if(_handle != 0) {
              OCIHandleFree(_handle, OCI_HTYPE_ENV);
              _handle = 0;
            }
          }

          OCIEnv* getHandle() const {
            return _handle;
          }
      
        private:
          Environment(const Environment& other);
          Environment& operator = (const Environment& other);

          OCIEnv* _handle;
      };
    }
  }
}

#endif /* _SK_OCI_DB_ENVIRONMENT_H_ */
