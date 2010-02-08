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
#include <sk/oci/Exception.h>
#include <sk/oci/NoDataException.h>
#include <sk/oci/ErrorException.h>
#include <sk/oci/InvalidHandleException.h>
#include <sk/oci/StillExecutingException.h>
#include <sk/oci/ContinueException.h>

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
  SK_OCI_ENSURE_SUCCESS(OCIHandleAlloc(_env.getHandle(), &_handle, _type, 0, 0));
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
  SK_OCI_ENSURE_SUCCESS(OCIAttrSet(_handle, _type, const_cast<void*>(attr), size, attrType, _error.getHandle()));
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

OraText* 
sk::oci::db::Handle::
toOraText(std::vector<char> buffer) const
{
  if(buffer.size() == 0) {
    throw sk::oci::Exception("toOraText", "Empty buffer");
  }
  return reinterpret_cast<OraText*>(&buffer.front());
}

void
sk::oci::db::Handle::
ensureSuccess(int status, const char* origin) const 
{
  switch(status) {
    case OCI_SUCCESS:
      break;
      
    case OCI_SUCCESS_WITH_INFO:
      _error.handleSuccessWithInfo(origin);
      break;
                                
    case OCI_NEED_DATA: 
      throw sk::oci::Exception(origin, "Need data");

    case OCI_NO_DATA:
      throw sk::oci::NoDataException(origin);

    case OCI_ERROR: {
      std::vector<char> buffer(1024, 0);
      sb4 code = _error.getError(buffer);

      throw sk::oci::ErrorException(origin, code, &buffer.front());
    }

    case OCI_INVALID_HANDLE: 
      throw sk::oci::InvalidHandleException(origin);

    case OCI_STILL_EXECUTING: 
      throw sk::oci::StillExecutingException(origin);

    case OCI_CONTINUE: 
      throw sk::oci::ContinueException(origin);

    default:
      throw sk::oci::Exception(origin, "Unknown OCI status " + sk::util::String::valueOf(status));
  }
}
