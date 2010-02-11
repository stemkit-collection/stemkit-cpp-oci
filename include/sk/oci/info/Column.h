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

          void setSchemaName(const sk::util::String& name);
          void setObjectName(const sk::util::String& name);
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          const sk::util::String inspect() const;
      
        private:
          Column& operator = (const Column& other);

          const sk::util::String _name;
          const info::Type& _type;
          const int _size;

          sk::util::String _schemaName;
          sk::util::String _objectName;
      };
    }
  }
}

#endif /* _SK_OCI_INFO_COLUMN_H_ */
