/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_STRINGS_H_
#define _SK_OCI_STRINGS_H_

#include <sk/util/CappedStrings.h>
#include <sk/oci/Value.h>

namespace sk {
  namespace oci {
    class Strings 
      : public sk::util::CappedStrings, 
        public virtual sk::oci::Value
    {
      public:
        Strings();
        Strings(int cap);
        virtual ~Strings();

        sk::oci::Strings& operator << (const sk::util::String& item);
    
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

#endif /* _SK_OCI_STRINGS_H_ */
