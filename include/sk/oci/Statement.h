/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_STATEMENT_H_
#define _SK_OCI_STATEMENT_H_

#include <sk/util/Object.h>
#include <sk/util/String.h>

namespace sk {
  namespace oci {
    class Statement 
      : public virtual sk::util::Object
    {
      public:
        virtual void setDescribeOnly(bool state) = 0;

        virtual void bindString(int position, int size, const sk::util::String& value) = 0;
        virtual void bindInt(int position, int value) = 0;

        virtual void bindString(const sk::util::String& placeholder, int size, const sk::util::String& value) = 0;
        virtual void bindInt(const sk::util::String& placeholder, int value) = 0;
    };
  }
}

#endif /* _SK_OCI_STATEMENT_H_ */
