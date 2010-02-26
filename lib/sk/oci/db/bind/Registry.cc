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
#include <sk/util/Holder.cxx>
#include <sk/util/ArrayList.cxx>

#include "Registry.h"
#include "Provider.h"
#include "Data.h"

#include <oci.h>

static const sk::util::String __className("sk::oci::db::bind::Registry");

sk::oci::db::bind::Registry::
Registry()
{
}

sk::oci::db::bind::Registry::
~Registry()
{
}

const sk::util::Class
sk::oci::db::bind::Registry::
getClass() const
{
  return sk::util::Class(__className);
}

int 
sk::oci::db::bind::Registry::
bindString(db::bind::Provider& provider, int position, int sze, const sk::util::String& value)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

int 
sk::oci::db::bind::Registry::
bindInteger(db::bind::Provider& provider, int position, uint32_t value)
{
  sk::util::Holder<db::bind::Data> holder(new db::bind::Data(provider.datasetSize(), position, SQLT_INT, &value, sizeof(value)));
  provider.bindDataPosition(holder.getMutable());

  int index = _depot.size();
  _depot.add(holder.release());

  return index;
}

int 
sk::oci::db::bind::Registry::
bindString(db::bind::Provider& provider, const sk::util::String& tag, int sze, const sk::util::String& value)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

int 
sk::oci::db::bind::Registry::
bindInteger(db::bind::Provider& provider, const sk::util::String& tag, uint32_t value)
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

const sk::oci::Data& 
sk::oci::db::bind::Registry::
boundDataAt(int index) const
{
  return _depot.get(index);
}
