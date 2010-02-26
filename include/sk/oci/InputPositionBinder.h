/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_INPUTPOSITIONBINDER_H_
#define _SK_OCI_INPUTPOSITIONBINDER_H_

#include <sk/util/Object.h>

namespace sk {
  namespace oci {
    class InputPositionBinder 
      : public virtual sk::util::Object
    {
      public:
        virtual int bindStringAt(int position, int size, const sk::util::String& value) = 0;
        virtual int bindIntAt(int position, uint32_t value) = 0;
    };
  }
}

#endif /* _SK_OCI_INPUTPOSITIONBINDER_H_ */
