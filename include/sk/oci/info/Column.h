/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_INFO_COLUMN_H_
#define _SK_OCI_INFO_COLUMN_H_

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <sk/oci/info/Type.h>

namespace sk {
  namespace oci {
    namespace info {
      class Column 
        : public virtual sk::util::Object
      {
        public:
          Column(const sk::util::String& name, const info::Type& type, uint32_t size);
          virtual ~Column();

          const sk::util::String getName() const;
          const sk::util::String getTypeName() const;
          const info::Type& getType() const;
          int getSize() const;

          void setTypeName(const sk::util::String& schema, const sk::util::String& object);
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          const sk::util::String inspect() const;
      
        private:
          Column& operator = (const Column& other);

          const sk::util::String _name;
          const info::Type& _type;
          const int _size;

          sk::util::String _typeName;
      };
    }
  }
}

#endif /* _SK_OCI_INFO_COLUMN_H_ */
