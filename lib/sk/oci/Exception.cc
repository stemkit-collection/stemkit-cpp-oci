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

#include <sk/oci/Exception.h>

static const sk::util::String __className("sk::oci::Exception");

namespace {
  const sk::util::String normalize_origin_function(const sk::util::String& origin) {
    int index = origin.indexOf('(');
    if(index == -1) {
      return origin;
    }
    return origin.substring(0, index);
  }

  const sk::util::String normalize_origin_namespace(const sk::util::String& origin) {
    int index = origin.lastIndexOf(':');
    if(index == -1) {
      return origin;
    }
    return origin.substring(index + 1);
  }

  const sk::util::String normalize_origin(const sk::util::String& origin) {
    return normalize_origin_namespace(normalize_origin_function(origin)).trim();
  }
}

sk::oci::Exception::
Exception(const sk::util::String& origin, const sk::util::String& message)
  : sk::util::Exception(join(normalize_origin(origin), message))
{
}

const sk::util::Class
sk::oci::Exception::
getClass() const
{
  return sk::util::Class(__className);
}

