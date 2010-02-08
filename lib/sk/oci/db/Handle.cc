/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "Handle.h"
#include "Environment.h"
#include "handle/Error.h"

sk::oci::db::Handle::
Handle(ub4 type, db::Environment& env, db::handle::Error& error)
  : _type(type), _env(env), _handle(0), _error(error) 
{
}

sk::oci::db::Handle::
~Handle()
{
  reset();
}

void 
sk::oci::db::Handle::
init() 
{
  OCIHandleAlloc(_env.getHandle(), &_handle, _type, 0, 0);
}

void 
sk::oci::db::Handle::
reset() 
{
  if(_handle != 0) {
    OCIHandleFree(_handle, _type);
    _handle = 0;
  }
}

void 
sk::oci::db::Handle::
setAttr(const void* attr, ub4 size, ub4 attrType) 
{
  OCIAttrSet(_handle, _type, const_cast<void*>(attr), size, attrType, _error.getHandle());
}

void* 
sk::oci::db::Handle::
getHandle() const 
{
  return _handle;
}

const OraText* 
sk::oci::db::Handle::
toOraText(const sk::util::String& string) const 
{
  return reinterpret_cast<const OraText*>(string.getChars());
}

