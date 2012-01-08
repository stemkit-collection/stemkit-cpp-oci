/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_OUTPUTTAGBINDER_H_
#define _SK_OCI_OUTPUTTAGBINDER_H_

#include <sk/util/Object.h>
#include <sk/util/Strings.h>
#include <sk/util/Integers.h>

namespace sk {
  namespace oci {
    class OutputTagBinder
      : public virtual sk::util::Object
    {
      public:
        virtual int bindCharsTag(const sk::util::String& tag, int size) = 0;
        virtual int bindIntTag(const sk::util::String& tag) = 0;
    };
  }
}

#endif /* _SK_OCI_OUTPUTTAGBINDER_H_ */
