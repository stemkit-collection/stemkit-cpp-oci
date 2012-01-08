/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_TRUNCATEDCOLUMNEXCEPTION_H_
#define _SK_OCI_TRUNCATEDCOLUMNEXCEPTION_H_

#include <sk/oci/ErrorException.h>

namespace sk {
  namespace oci {
    class TruncatedColumnException
      : public sk::oci::ErrorException
    {
      public:
        TruncatedColumnException(const sk::util::String& origin, int code, const sk::util::String& message);

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_OCI_TRUNCATEDCOLUMNEXCEPTION_H_ */
