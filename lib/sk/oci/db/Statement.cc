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

#include "Statement.h"
#include "bind/Data.h"

static const sk::util::String __className("sk::oci::db::Statement");

sk::oci::db::Statement::
Statement(db::handle::Error& error, const sk::util::String& sql)
  : db::Handle(OCI_HTYPE_STMT, error.environment(), error), _mode(OCI_DEFAULT), _iterations(1), _offset(0),
    _useColumnCodes(false), _useTruncate(false), _info(false)
{
  init();
  SK_OCI_ENSURE_SUCCESS(OCIStmtPrepare(getHandle(), error.getHandle(), toOraText(sql), sql.length(), OCI_NTV_SYNTAX, OCI_DEFAULT));
  _type = getIntAttr(OCI_ATTR_STMT_TYPE);

  if(isSelect() == true) {
    _iterations = 0;
  }
}

sk::oci::db::Statement::
~Statement()
{
  reset();
}

const sk::util::Class
sk::oci::db::Statement::
getClass() const
{
  return sk::util::Class(__className);
}

OCIStmt* 
sk::oci::db::Statement::
getHandle() const 
{
  return reinterpret_cast<OCIStmt*>(db::Handle::getHandle());
}

void 
sk::oci::db::Statement::
execute(db::handle::Service& service) 
{
  SK_OCI_ENSURE_SUCCESS(OCIStmtExecute(service.getHandle(), getHandle(), error().getHandle(), _iterations, _offset, 0, 0, _mode));
  _offset += _iterations;
}

void
sk::oci::db::Statement::
useTruncate(bool state) 
{
  _useTruncate = state;
}

void
sk::oci::db::Statement::
useColumnCodes(bool state) 
{
  _useColumnCodes = state;
}

bool 
sk::oci::db::Statement::
isSelect() const
{
  return _type == OCI_STMT_SELECT;
}

bool 
sk::oci::db::Statement::
isUpdate() const
{
  return _type == OCI_STMT_UPDATE;
}

bool 
sk::oci::db::Statement::
isDelete() const
{
  return _type == OCI_STMT_DELETE;
}

bool 
sk::oci::db::Statement::
isInsert() const
{
  return _type == OCI_STMT_INSERT;
}

bool 
sk::oci::db::Statement::
isCreate() const
{
  return _type == OCI_STMT_CREATE;
}

bool 
sk::oci::db::Statement::
isDrop() const
{
  return _type == OCI_STMT_DROP;
}

bool 
sk::oci::db::Statement::
isAlter() const
{
  return _type == OCI_STMT_ALTER;
}

bool 
sk::oci::db::Statement::
isBegin() const
{
  return _type == OCI_STMT_BEGIN;
}

bool 
sk::oci::db::Statement::
isDeclare() const
{
  return _type == OCI_STMT_DECLARE;
}

void 
sk::oci::db::Statement::
setDescribeOnly(bool state)
{
  _mode = (state == true ? OCI_DESCRIBE_ONLY : OCI_DEFAULT);
}

void
sk::oci::db::Statement::
setIterations(uint32_t number)
{
  _iterations = number;
}

uint32_t
sk::oci::db::Statement::
datasetSize() const
{
  return _iterations;
}

void
sk::oci::db::Statement::
setRowOffset(uint32_t number)
{
  _offset = number;
}

const sk::oci::Data& 
sk::oci::db::Statement::
boundData(int bid) const
{
  return _bindRegistry.boundData(bid);
}

sk::oci::Data& 
sk::oci::db::Statement::
boundMutableData(int bid)
{
  return _bindRegistry.boundMutableData(bid);
}

int
sk::oci::db::Statement::
bindCharsAt(int position, int size, const sk::util::Strings& values)
{
  return _bindRegistry.bindChars(*this, position, size, values);
}

int
sk::oci::db::Statement::
bindIntAt(int position, const sk::util::Integers& values)
{
  return _bindRegistry.bindInteger(*this, position, values);
}

int
sk::oci::db::Statement::
bindCharsTag(const sk::util::String& tag, int size, const sk::util::Strings& values)
{
  return _bindRegistry.bindChars(*this, tag, size, values);
}

int
sk::oci::db::Statement::
bindIntTag(const sk::util::String& tag, const sk::util::Integers& values)
{
  return _bindRegistry.bindInteger(*this, tag, values);
}

int
sk::oci::db::Statement::
bindCharsAt(int position, int size)
{
  return _bindRegistry.bindChars(*this, position, size);
}

int
sk::oci::db::Statement::
bindIntAt(int position)
{
  return _bindRegistry.bindInteger(*this, position);
}

int
sk::oci::db::Statement::
bindCharsTag(const sk::util::String& tag, int size)
{
  return _bindRegistry.bindChars(*this, tag, size);
}

int
sk::oci::db::Statement::
bindIntTag(const sk::util::String& tag)
{
  return _bindRegistry.bindInteger(*this, tag);
}

void
sk::oci::db::Statement::
bindDataPosition(db::bind::Data& data)
{
  SK_OCI_ENSURE_SUCCESS(
    OCIBindByPos(
      getHandle(), 
      &data.bindHandle(), 
      error().getHandle(), 
      data.position(), 
      data.valuePointer(), 
      data.valueSize(), 
      data.type(), 
      data.indicatorPointer(), 
      data.sizePointer(), 
      (_useColumnCodes ? data.columnCodePointer() : 0), 
      0, 0, 
      OCI_DEFAULT
    )
  );
}

void
sk::oci::db::Statement::
bindDataTag(db::bind::Data& data)
{
  SK_OCI_ENSURE_SUCCESS(
    OCIBindByName(
      getHandle(), 
      &data.bindHandle(), 
      error().getHandle(), 
      data.tagPointer(), 
      data.tagSize(), 
      data.valuePointer(), 
      data.valueSize(), 
      data.type(), 
      data.indicatorPointer(), 
      data.sizePointer(), 
      (_useColumnCodes ? data.columnCodePointer() : 0), 
      0, 0, 
      OCI_DEFAULT
    )
  );
}

void
sk::oci::db::Statement::
defineDataPosition(db::bind::Data& data)
{
  SK_OCI_ENSURE_SUCCESS(
    OCIDefineByPos(
      getHandle(), 
      &data.defineHandle(), 
      error().getHandle(), 
      data.position(), 
      data.valuePointer(), 
      data.valueSize(), 
      data.type(), 
      data.indicatorPointer(), 
      data.sizePointer(), 
      (_useColumnCodes ? data.columnCodePointer() : 0), 
      OCI_DEFAULT
    )
  );
}

sk::oci::db::bind::Registry&
sk::oci::db::Statement::
bindRegistry()
{
  return _bindRegistry;
}

void
sk::oci::db::Statement::
fetch(uint32_t amount)
{
  int status = OCIStmtFetch2(
    getHandle(), 
    error().getHandle(), 
    amount,
    OCI_FETCH_NEXT,
    0,
    OCI_DEFAULT
  );

  _info = false;
  switch(status) {
    case OCI_NO_DATA:
      break;

    case OCI_SUCCESS_WITH_INFO:
      _info = true;
      break;

    default:
      ensureSuccess(status, "fetch");
  }
}

bool
sk::oci::db::Statement::
hasInfo() const
{
  return _info;
}

sb4
sk::oci::db::Statement::
mapOracleError(sb4 code) const 
{
  switch(code) {
    case 1406:
      if(_useTruncate == false) {
        break;
      }
      return 0;

    case 1002: // ORA-01002: fetch out of sequence
      return 0;
  }
  return code;
}

uint32_t 
sk::oci::db::Statement::
obtainRowCount()
{
  return getIntAttr(OCI_ATTR_ROW_COUNT);
}

