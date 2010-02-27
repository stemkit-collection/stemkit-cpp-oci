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
#include <sk/oci/TruncatedColumnException.h>

sk::oci::db::Handle::
Handle(ub4 type, db::Environment& env, db::handle::Error& error)
  : _type(type), _environment(env), _handle(0), _error(error) 
{
}

sk::oci::db::Handle::
~Handle()
{
}

void 
sk::oci::db::Handle::
init() 
{
  SK_OCI_ENSURE_SUCCESS(OCIHandleAlloc(_environment.getHandle(), &_handle, _type, 0, 0));
}

void 
sk::oci::db::Handle::
init(void* handle) 
{
  _handle = handle;
}

void 
sk::oci::db::Handle::
reset() 
{
  if(_handle != 0) {
    sword status = OCIHandleFree(_handle, _type);
    if(status != OCI_SUCCESS) {
      _handle = 0;
      throw sk::oci::Exception("OCIHandleFree", "status=" + sk::util::String::valueOf(status));
    }
    _handle = 0;
  }
}

void 
sk::oci::db::Handle::
setAttr(const void* attr, ub4 size, ub4 attrType) 
{
  SK_OCI_ENSURE_SUCCESS(OCIAttrSet(_handle, _type, const_cast<void*>(attr), size, attrType, _error.getHandle()));
}

ub4
sk::oci::db::Handle::
getIntAttr(ub4 attrType)
{
  ub4 value = 0;
  SK_OCI_ENSURE_SUCCESS(OCIAttrGet(_handle, _type, &value, 0, attrType, _error.getHandle()));

  return value;
}

ub2
sk::oci::db::Handle::
getShortAttr(ub4 attrType)
{
  ub2 value = 0;
  SK_OCI_ENSURE_SUCCESS(OCIAttrGet(_handle, _type, &value, 0, attrType, _error.getHandle()));

  return value;
}

const char*
sk::oci::db::Handle::
getCStrAttr(uint32_t* length, ub4 attrType)
{
  ub4 size = 0;
  void* location = 0;
  SK_OCI_ENSURE_SUCCESS(OCIAttrGet(_handle, _type, &location, &size, attrType, _error.getHandle()));

  *length = size;
  return reinterpret_cast<const char*>(location);
}

bool
sk::oci::db::Handle::
haveHandle() const 
{
  return _handle != 0;
}

void* 
sk::oci::db::Handle::
getHandle() const 
{
  return _handle;
}

sk::oci::db::handle::Error&
sk::oci::db::Handle::
error() const 
{
  return _error;
}

ub4
sk::oci::db::Handle::
type() const 
{
  return _type;
}

sk::oci::db::Environment&
sk::oci::db::Handle::
environment() const 
{
  return _environment;
}

const OraText* 
sk::oci::db::Handle::
toOraText(const sk::util::String& string) const 
{
  return reinterpret_cast<const OraText*>(string.getChars());
}

OraText* 
sk::oci::db::Handle::
toOraText(std::vector<char>& buffer) const
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

      switch(code) {
        case 1406:
          throw sk::oci::TruncatedColumnException(origin);
      }
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
