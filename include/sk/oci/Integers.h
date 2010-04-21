/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_INTEGERS_H_
#define _SK_OCI_INTEGERS_H_

#include <sk/util/Integers.h>
#include <sk/oci/Value.h>

namespace sk {
  namespace oci {
    class Integers 
      : public sk::util::Integers,
        public virtual sk::oci::Value
    {
      public:
        Integers();
        virtual ~Integers();
    
        sk::oci::Integers& operator << (const uint32_t& item);

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      protected:
        // sk::oci::Value implementation.
        void bindTag(const sk::util::String& tag, sk::oci::Statement& statement) const;
        void bindPosition(int position, sk::oci::Statement& statement) const;
        int bindPosition(int position, sk::oci::Cursor& cursor) const;
        void assume(const sk::oci::Data& data);
    };
  }
}

#endif /* _SK_OCI_INTEGERS_H_ */
