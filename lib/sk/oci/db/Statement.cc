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
#include "Data.h"

static const sk::util::String __className("sk::oci::db::Statement");

sk::oci::db::Statement::
Statement(db::handle::Error& error, const sk::util::String& sql)
  : db::Handle(OCI_HTYPE_STMT, error.environment(), error), _mode(OCI_DEFAULT)
{
  init();
  SK_OCI_ENSURE_SUCCESS(OCIStmtPrepare(getHandle(), error.getHandle(), toOraText(sql), sql.length(), OCI_NTV_SYNTAX, OCI_DEFAULT));
  _type = getIntAttr(OCI_ATTR_STMT_TYPE);
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
  SK_OCI_ENSURE_SUCCESS(OCIStmtExecute(service.getHandle(), getHandle(), error().getHandle(), 0, 0, 0, 0, _mode));
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

int
sk::oci::db::Statement::
bindStringAt(int position, int size, const sk::util::String& value)
{
  return bindDataPosition(_binder.bindString(position, size, value));
}

int
sk::oci::db::Statement::
bindIntAt(int position, uint32_t value)
{
  return bindDataPosition(_binder.bindInteger(position, value));
}

int
sk::oci::db::Statement::
bindStringTag(const sk::util::String& tag, int size, const sk::util::String& value)
{
  return bindDataTag(_binder.bindString(tag, size, value));
}

int
sk::oci::db::Statement::
bindIntTag(const sk::util::String& tag, uint32_t value)
{
  return bindDataTag(_binder.bindInteger(tag, value));
}

int
sk::oci::db::Statement::
bindDataPosition(db::Data& data)
{
  SK_OCI_ENSURE_SUCCESS(OCIBindByPos(getHandle(), &bindp, error().getHandle(), data.index(), data.valuePointer(), data.valueSize(), data.type(), data.indicatorPointer(), 0, 0, 0, 0, OCI_DEFAULT));
  return data.index();
}

int
sk::oci::db::Statement::
bindDataTag(db::Data& data)
{
  SK_OCI_ENSURE_SUCCESS(OCIBindByName(getHandle(), 0, error().getHandle(), data.tagPointer(), data.tagSize(), data.valuePointer(), data.valueSize(), data.type(), data.indicatorPointer(), 0, 0, 0, 0, OCI_DEFAULT));
  return data.index();
}

const sk::oci::BindRegistry&
sk::oci::db::Statement::
bindRegistry() const
{
  return _binder;
}
