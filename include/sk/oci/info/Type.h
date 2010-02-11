/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_INFO_TYPE_H_
#define _SK_OCI_INFO_TYPE_H_

#include <sk/util/Object.h>
#include <vector>

namespace sk {
  namespace oci {
    namespace info {
      class Type 
        : public virtual sk::util::Object
      {
        public:
          virtual ~Type();

          static const info::Type& valueOf(const sk::util::String& name);
          static const info::Type& valueOf(int value);

          const sk::util::String getName() const;
          int toInt() const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
          const sk::util::String toString() const;

          bool operator == (const info::Type& other);
      
          static const info::Type SK_UNKNOWN;
          static const info::Type SK_NUMBER;
          static const info::Type SK_VARCHAR2;
          static const info::Type SK_VARCHAR;
          static const info::Type SK_CHAR;
          static const info::Type SK_REF;
          static const info::Type SK_DATE;
          static const info::Type SK_REAL;
          static const info::Type SK_DOUBLE;
          static const info::Type SK_FLOAT;
          static const info::Type SK_DECIMAL;
          static const info::Type SK_OCTET;
          static const info::Type SK_INTEGER;
          static const info::Type SK_SMALLINT;
          static const info::Type SK_RAW;
          static const info::Type SK_VARRAY;
          static const info::Type SK_TABLE;
          static const info::Type SK_CLOB;
          static const info::Type SK_BLOB;
          static const info::Type SK_BFILE;
          static const info::Type SK_OBJECT;
          static const info::Type SK_NAMEDCOLLECTION;
      
        private:
          Type(const sk::util::String& name);
          Type(const Type& other);
          Type& operator = (const Type& other);

          typedef std::vector<info::Type*> container_t;
          static container_t _types;
          static int _counter;

          int _value;
          const sk::util::String _name;
      };
    }
  }
}

#endif /* _SK_OCI_INFO_TYPE_H_ */
