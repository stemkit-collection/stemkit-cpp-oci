/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_OCI_DB_BIND_PIECE_H_
#define _SK_OCI_DB_BIND_PIECE_H_

#include <sk/oci/Data.h>

namespace sk {
  namespace oci {
    namespace db {
      namespace bind {
        class Data;

        class Piece
          : public virtual sk::oci::Data
        {
          public:
            Piece(int index, bind::Data& data);
            virtual ~Piece();

            // sk::oci::Data implementation.
            const sk::oci::Data& piece(int index) const;
            sk::oci::Data& piece(int index);

            const sk::util::String info() const;

            const int32_t& intValue() const;
            const char* charsValue() const;
            const sk::util::String stringValue() const;

            void setIntValue(int32_t value);
            void setCharsValue(const sk::util::String& value);
            void setNull(bool state);

            uint32_t size() const;
            uint32_t columnCode() const;

            bool isNull() const;
            bool isTruncated() const;

            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;
            const sk::util::String toString() const;
            const sk::util::String inspect() const;

          private:
            Piece(const Piece& other);
            Piece& operator = (const Piece& other);

            const int _index;
            bind::Data& _data;
        };
      }
    }
  }
}

#endif /* _SK_OCI_DB_BIND_PIECE_H_ */
