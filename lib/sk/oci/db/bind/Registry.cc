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
#include "IntData.h"
#include "StringData.h"

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
bindString(db::bind::Provider& provider, int position, int size, const sk::util::String& value)
{
  return bindData(provider, position, new db::bind::StringData(provider.datasetSize(), position, size, value));
}

int 
sk::oci::db::bind::Registry::
bindString(db::bind::Provider& provider, int position, int size)
{
  return bindData(provider, position, new db::bind::StringData(provider.datasetSize(), position, size));
}

int 
sk::oci::db::bind::Registry::
bindInteger(db::bind::Provider& provider, int position, uint32_t value)
{
  return bindData(provider, position, new db::bind::IntData(provider.datasetSize(), position, value));
}

int 
sk::oci::db::bind::Registry::
bindInteger(db::bind::Provider& provider, int position)
{
  return bindData(provider, position, new db::bind::IntData(provider.datasetSize(), position));
}

int 
sk::oci::db::bind::Registry::
bindString(db::bind::Provider& provider, const sk::util::String& tag, int size, const sk::util::String& value)
{
  return bindData(provider, tag, new db::bind::StringData(provider.datasetSize(), tag, size, value));
}

int 
sk::oci::db::bind::Registry::
bindString(db::bind::Provider& provider, const sk::util::String& tag, int size)
{
  return bindData(provider, tag, new db::bind::StringData(provider.datasetSize(), tag, size));
}

int 
sk::oci::db::bind::Registry::
bindInteger(db::bind::Provider& provider, const sk::util::String& tag, uint32_t value)
{
  return bindData(provider, tag, new db::bind::IntData(provider.datasetSize(), tag, value));
}

int 
sk::oci::db::bind::Registry::
bindInteger(db::bind::Provider& provider, const sk::util::String& tag)
{
  return bindData(provider, tag, new db::bind::IntData(provider.datasetSize(), tag));
}

int
sk::oci::db::bind::Registry::
bindData(db::bind::Provider& provider, int position, db::bind::Data* data)
{
  sk::util::Holder<db::bind::Data> holder(data);
  provider.bindDataPosition(holder.getMutable());

  int index = _depot.size();
  _depot.add(holder.release());

  return index;
}

int
sk::oci::db::bind::Registry::
bindData(db::bind::Provider& provider, const sk::util::String& tag, db::bind::Data* data)
{
  sk::util::Holder<db::bind::Data> holder(data);
  provider.bindDataTag(holder.getMutable());

  int index = _depot.size();
  _depot.add(holder.release());

  return index;
}

const sk::oci::Data& 
sk::oci::db::bind::Registry::
boundDataAt(int index) const
{
  return _depot.get(index);
}
