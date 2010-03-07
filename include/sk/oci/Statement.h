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
#include <sk/oci/OutputPositionBinder.h>
#include <sk/oci/InputTagBinder.h>
#include <sk/oci/OutputTagBinder.h>
#include <sk/oci/BindRegistry.h>

namespace sk {
  namespace oci {
    class Statement 
      : public virtual sk::oci::InputPositionBinder,
        public virtual sk::oci::InputTagBinder,
        public virtual sk::oci::OutputPositionBinder,
        public virtual sk::oci::OutputTagBinder,
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
        virtual void setRowOffset(uint32_t number) = 0;

        // Resolving ambiguity between input and output binders.
        virtual int bindCharsAt(int position, int size, const sk::util::Strings& values) = 0;
        virtual int bindCharsAt(int position, int size) = 0;
        virtual int bindIntAt(int position, const sk::util::Integers& values) = 0;
        virtual int bindIntAt(int position) = 0;
        virtual int bindCharsTag(const sk::util::String& tag, int size, const sk::util::Strings& values) = 0;
        virtual int bindCharsTag(const sk::util::String& tag, int size) = 0;
        virtual int bindIntTag(const sk::util::String& tag, const sk::util::Integers& values) = 0;
        virtual int bindIntTag(const sk::util::String& tag) = 0;
    };
  }
}

#endif /* _SK_OCI_STATEMENT_H_ */
