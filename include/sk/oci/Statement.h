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
#include <sk/oci/InputPositionBinder.h>
#include <sk/oci/InputTagBinder.h>
#include <sk/oci/BindRegistry.h>

namespace sk {
  namespace oci {
    class Statement 
      : public virtual sk::oci::InputPositionBinder,
        public virtual sk::oci::InputTagBinder,
        public virtual sk::oci::BindRegistry
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
        virtual void setIterations(uint32_t number) = 0;
        virtual void setRowOffset(uint32_t number) = 0;
    };
  }
}

#endif /* _SK_OCI_STATEMENT_H_ */
