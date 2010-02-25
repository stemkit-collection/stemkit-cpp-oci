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
        virtual bool isSelect() const = 0;
        virtual bool isUpdate() const = 0;
        virtual bool isDelete() const = 0;
        virtual bool isInsert() const = 0;
        virtual bool isCreate() const = 0;
        virtual bool isDrop() const = 0;
        virtual bool isAlter() const = 0;
        virtual bool isBegin() const = 0;
        virtual bool isDeclare() const = 0;

        virtual void setDescribeOnly(bool state) = 0;

        virtual int bindStringAt(int position, int size, const sk::util::String& value) = 0;
        virtual int bindIntAt(int position, uint32_t value) = 0;

        virtual int bindStringTag(const sk::util::String& tag, int size, const sk::util::String& value) = 0;
        virtual int bindIntTag(const sk::util::String& tag, uint32_t value) = 0;
    };
  }
}

#endif /* _SK_OCI_STATEMENT_H_ */
