/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_NODATAEXCEPTION_H_
#define _SK_OCI_NODATAEXCEPTION_H_

#include <sk/oci/Exception.h>

namespace sk {
  namespace oci {
    class NoDataException
      : public sk::oci::Exception
    {
      public:
        NoDataException(const sk::util::String& origin);

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    };
  }
}

#endif /* _SK_OCI_NODATAEXCEPTION_H_ */
