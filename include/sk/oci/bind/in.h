/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_BIND_IN_H_
#define _SK_OCI_BIND_IN_H_

#include <sk/util/Object.h>
#include <sk/oci/Integers.h>
#include <sk/oci/Strings.h>
#include <sk/oci/Bind.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace oci {
    namespace bind {
      class in 
        : public sk::oci::Bind
      {
        public:
          in();
          virtual ~in();

          sk::oci::bind::in& operator<<(const sk::oci::Integers& data);
          sk::oci::bind::in& operator<<(const sk::oci::Strings& data);
          sk::oci::bind::in& operator<<(const sk::util::String& tag);
          sk::oci::bind::in& operator<<(const char* tag);
          sk::oci::bind::in& operator<<(int position);

          using sk::oci::Bind::operator<<;
      
          // sk::oci::Bind implementation.
          void prepareStatement(sk::oci::Statement& statement) const;
          void processCursor(sk::oci::Cursor& cursor, sk::oci::bind::Data& data) const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          in& operator = (const in& other);

          void analyzeCardinality(int cardinality);

          struct Data;
          sk::util::Holder<Data>::Sharing _dataHolder;
          Data& _data;
      };
    }
  }
}

#endif /* _SK_OCI_BIND_IN_H_ */
