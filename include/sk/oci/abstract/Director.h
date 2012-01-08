/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_ABSTRACT_DIRECTOR_H_
#define _SK_OCI_ABSTRACT_DIRECTOR_H_

#include <sk/oci/Director.h>

namespace sk {
  namespace oci {
    class Statement;
    class Cursor;

    namespace abstract {
      class Director : public virtual sk::oci::Director {
        public:
          void prepareStatement(sk::oci::Statement& statement) const {
          }

          void processCursor(sk::oci::Cursor& cursor) const {
          }

          bool nextIteration() const {
            return false;
          }
      };
    }
  }
}

#endif /* _SK_OCI_ABSTRACT_DIRECTOR_H_ */
