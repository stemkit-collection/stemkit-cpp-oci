/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_BIND_REGISTRY_H_
#define _SK_OCI_DB_BIND_REGISTRY_H_

#include <sk/util/ArrayList.hxx>
#include <sk/util/Integers.h>
#include <sk/oci/Data.h>
#include "Provider.h"

namespace sk {
  namespace oci {
    namespace db {
      namespace bind {
        class Data;

        class Registry
          : public virtual sk::util::Object
        {
          public:
            Registry();
            virtual ~Registry();

            int bindChars(db::bind::Provider& provider, int position, int size, const sk::util::Strings& values);
            int bindChars(db::bind::Provider& provider, int position, int size);

            int bindInteger(db::bind::Provider& provider, int position, const sk::util::Integers& values);
            int bindInteger(db::bind::Provider& provider, int position);

            int bindChars(db::bind::Provider& provider, const sk::util::String& tag, int size, const sk::util::Strings& values);
            int bindChars(db::bind::Provider& provider, const sk::util::String& tag, int size);

            int bindInteger(db::bind::Provider& provider, const sk::util::String& tag, const sk::util::Integers& values);
            int bindInteger(db::bind::Provider& provider, const sk::util::String& tag);

            const sk::oci::Data& boundData(int bid) const;
            sk::oci::Data& boundMutableData(int bid);

            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;

          private:
            Registry(const Registry& other);
            Registry& operator = (const Registry& other);

            int bindData(db::bind::Provider& provider, int position, db::bind::Data* data);
            int bindData(db::bind::Provider& provider, const sk::util::String& tag, db::bind::Data* data);

            sk::util::ArrayList<db::bind::Data> _depot;
        };
      }
    }
  }
}

#endif /* _SK_OCI_DB_BIND_REGISTRY_H_ */
