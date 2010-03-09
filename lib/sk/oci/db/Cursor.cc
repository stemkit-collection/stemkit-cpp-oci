/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/UnsupportedOperationException.h>
#include <sk/util/IndexOutOfBoundsException.h>
#include <sk/oci/TruncatedColumnException.h>
#include <sk/oci/info/Column.h>
#include "handle/Parameter.h"

#include "Cursor.h"

static const sk::util::String __className("sk::oci::db::Cursor");

sk::oci::db::Cursor::
Cursor(db::Statement& statement)
  : _statement(statement), _haveColumnCount(false), _capacity(1), _rowCount(0)
{
}

sk::oci::db::Cursor::
~Cursor()
{
}

const sk::util::Class
sk::oci::db::Cursor::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::oci::db::Cursor::
useTruncate(bool state)
{
  _statement.useTruncate(state);
}

void 
sk::oci::db::Cursor::
useColumnCodes(bool state)
{
  _statement.useColumnCodes(state);
}

uint32_t 
sk::oci::db::Cursor::
rowCount()
{
  return _rowCount;
}

uint32_t
sk::oci::db::Cursor::
columnCount()
{
  if(_haveColumnCount == false) {
    _columnCount = _statement.getIntAttr(OCI_ATTR_PARAM_COUNT);
    _haveColumnCount = true;
  }
  return _columnCount;
}

namespace {
  const sk::oci::info::Type& map_column_type(ub2 type) {
    switch(type) {
      case OCI_TYPECODE_NUMBER:
        return sk::oci::info::Type::SK_NUMBER;

      case OCI_TYPECODE_VARCHAR2:
        return sk::oci::info::Type::SK_VARCHAR2;

      case OCI_TYPECODE_VARCHAR:
        return sk::oci::info::Type::SK_VARCHAR;

      case OCI_TYPECODE_CHAR:
        return sk::oci::info::Type::SK_CHAR;

      case OCI_TYPECODE_REF:
        return sk::oci::info::Type::SK_REF;

      case OCI_TYPECODE_DATE:
        return sk::oci::info::Type::SK_DATE;

      case OCI_TYPECODE_REAL:
        return sk::oci::info::Type::SK_REAL;

      case OCI_TYPECODE_DOUBLE:
        return sk::oci::info::Type::SK_DOUBLE;

      case OCI_TYPECODE_FLOAT:
        return sk::oci::info::Type::SK_FLOAT;

      case OCI_TYPECODE_DECIMAL:
        return sk::oci::info::Type::SK_DECIMAL;

      case OCI_TYPECODE_OCTET:
        return sk::oci::info::Type::SK_OCTET;

      case OCI_TYPECODE_INTEGER:
        return sk::oci::info::Type::SK_INTEGER;

      case OCI_TYPECODE_SMALLINT:
        return sk::oci::info::Type::SK_SMALLINT;

      case OCI_TYPECODE_RAW:
        return sk::oci::info::Type::SK_RAW;

      case OCI_TYPECODE_VARRAY:
        return sk::oci::info::Type::SK_VARRAY;

      case OCI_TYPECODE_TABLE:
        return sk::oci::info::Type::SK_TABLE;

      case OCI_TYPECODE_CLOB:
        return sk::oci::info::Type::SK_CLOB;

      case OCI_TYPECODE_BLOB:
        return sk::oci::info::Type::SK_BLOB;

      case OCI_TYPECODE_BFILE:
        return sk::oci::info::Type::SK_BFILE;

      case OCI_TYPECODE_OBJECT:
        return sk::oci::info::Type::SK_OBJECT;

      case OCI_TYPECODE_NAMEDCOLLECTION:
        return sk::oci::info::Type::SK_NAMEDCOLLECTION;

      default:
        return sk::oci::info::Type::SK_UNKNOWN;
    }
  }
}

const sk::oci::info::Column 
sk::oci::db::Cursor::
columnAt(int index)
{
  if((index < 0) || index >= columnCount()) {
    throw sk::util::IndexOutOfBoundsException(SK_METHOD);
  }
  handle::Parameter parameter(_statement, index + 1);
  ub2 type = parameter.getShortAttr(OCI_ATTR_DATA_TYPE);

  ub4 char_semantics = parameter.getIntAttr(OCI_ATTR_CHAR_USED);
  ub2 size = parameter.getShortAttr(char_semantics ? OCI_ATTR_CHAR_SIZE : OCI_ATTR_DATA_SIZE);

  uint32_t length = 0;
  const char* name = parameter.getCStrAttr(&length, OCI_ATTR_NAME);

  info::Column column(sk::util::String(name, length), map_column_type(type), size);

  if((type == OCI_TYPECODE_OBJECT) || (type == OCI_TYPECODE_NAMEDCOLLECTION)) {
    uint32_t schema_length = 0;
    uint32_t object_length = 0;

    const char* schema_name = parameter.getCStrAttr(&schema_length, OCI_ATTR_SCHEMA_NAME);
    const char* object_name = parameter.getCStrAttr(&object_length, OCI_ATTR_TYPE_NAME);

    column.setTypeName(sk::util::String(schema_name, schema_length), sk::util::String(object_name, object_length));
  }
  return column;
}

void 
sk::oci::db::Cursor::
forEachColumn(const sk::util::Processor<const info::Column>& processor)
{
  int number = columnCount();
  for(int index=0; index < number; ++index) {
    processor.process(columnAt(index));
  }
}

void
sk::oci::db::Cursor::
setCapacity(uint32_t capacity)
{
  _capacity = capacity;
}

uint32_t
sk::oci::db::Cursor::
datasetSize() const
{
  return _capacity;
}

bool
sk::oci::db::Cursor::
hasInfo() const
{
  return _statement.hasInfo();
}

uint32_t
sk::oci::db::Cursor::
fetch()
{
  try {
    _statement.fetch(_capacity);
    return updateRowCount();
  }
  catch(const sk::oci::Exception& exception) {
    updateRowCount();
    throw;
  }
}

uint32_t
sk::oci::db::Cursor::
updateRowCount()
{
  uint32_t db_row_count = _statement.obtainRowCount();
  uint32_t delta = db_row_count - _rowCount;

  _rowCount = db_row_count;

  return delta;
}

const sk::oci::Data& 
sk::oci::db::Cursor::
boundData(int bid) const
{
  return _statement.bindRegistry().boundData(bid);
}

sk::oci::Data& 
sk::oci::db::Cursor::
boundMutableData(int bid)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

int 
sk::oci::db::Cursor::
bindIntAt(int position)
{
  return _statement.bindRegistry().bindInteger(*this, position);
}

int 
sk::oci::db::Cursor::
bindCharsAt(int position, int size)
{
  return _statement.bindRegistry().bindChars(*this, position, size);
}

void 
sk::oci::db::Cursor::
bindDataPosition(db::bind::Data& data)
{
  _statement.defineDataPosition(data);
}

void 
sk::oci::db::Cursor::
bindDataTag(db::bind::Data& data)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

