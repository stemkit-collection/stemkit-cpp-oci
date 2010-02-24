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

namespace sk {
  namespace oci {
    class Data 
      : public virtual sk::util::Object
    {
      public:
        virtual int intValue() const = 0;
        virtual const std::vector<char>& stringValue() const = 0;
        virtual bool isNull() const = 0;
    };
  }
}

#endif /* _SK_OCI_DATA_H_ */
