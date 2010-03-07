/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_CURSOR_H_
#define _SK_OCI_CURSOR_H_

#include <sk/util/Object.h>
#include <sk/util/Processor.h>
#include <sk/oci/info/Column.h>
#include <sk/oci/BindRegistry.h>
#include <sk/oci/OutputPositionBinder.h>

namespace sk {
  namespace oci {
    class Cursor 
      : public virtual oci::OutputPositionBinder,
        public virtual oci::BindRegistry
    {
      public:
        virtual uint32_t rowCount() = 0;
        virtual uint32_t columnCount() = 0;
        virtual const info::Column columnAt(int index) = 0;
        virtual void forEachColumn(const sk::util::Processor<const info::Column>& processor) = 0;

        virtual uint32_t fetch() = 0;
        virtual bool hasInfo() const = 0;

        virtual void useTruncate(bool state) = 0;
        virtual void useColumnCodes(bool state) = 0;
    };
  }
}

#endif /* _SK_OCI_CURSOR_H_ */
