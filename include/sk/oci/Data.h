/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DATA_H_
#define _SK_OCI_DATA_H_

#include <sk/util/Object.h>
#include <sk/util/Container.h>

namespace sk {
  namespace oci {
    class Data 
      : public virtual sk::util::Object
    {
      public:
        virtual const sk::util::String info() const = 0;

        virtual uint32_t& intValue() = 0;
        virtual const uint32_t& intValue() const = 0;

        virtual sk::util::Container& stringValue() = 0;
        virtual const sk::util::Container& stringValue() const = 0;

        virtual bool isNull() const = 0;
        virtual bool isTruncated() const = 0;
        virtual uint32_t getSize() const = 0;
        virtual uint32_t getColumnCode() const = 0;
    };
  }
}

#endif /* _SK_OCI_DATA_H_ */
