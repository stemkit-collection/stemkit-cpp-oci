/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_OUTPUTPOSITIONBINDER_H_
#define _SK_OCI_OUTPUTPOSITIONBINDER_H_

#include <sk/util/Object.h>

namespace sk {
  namespace oci {
    class OutputPositionBinder 
      : public virtual sk::util::Object
    {
      public:
        virtual int bindCharsAt(int position, int size) = 0;
        virtual int bindIntAt(int position) = 0;
    };
  }
}

#endif /* _SK_OCI_OUTPUTPOSITIONBINDER_H_ */
