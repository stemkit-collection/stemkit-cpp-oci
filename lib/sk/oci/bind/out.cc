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
#include <sk/util/Holder.cxx>

#include <sk/oci/bind/out.h>

static const sk::util::String __className("sk::oci::bind::out");

struct sk::oci::bind::out::Data : public virtual sk::util::Object {
  Data(int amount, int skip)
    : amount(amount), skip(skip) {}

  int amount;
  int skip;
};

sk::oci::bind::out::
out()
  : _dataHolder(new out::Data(0, 0)), _data(_dataHolder.getMutable())
{
}

sk::oci::bind::out::
out(uint32_t amount)
  : _dataHolder(new out::Data(amount, 0)), _data(_dataHolder.getMutable())
{
}

sk::oci::bind::out::
out(uint32_t amount, uint32_t skip)
  : _dataHolder(new out::Data(amount, skip)), _data(_dataHolder.getMutable())
{
}

sk::oci::bind::out::
~out()
{
}

const sk::util::Class
sk::oci::bind::out::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::oci::bind::out::
prepareStatement(sk::oci::Statement& statement) const
{
}

void 
sk::oci::bind::out::
processCursor(sk::oci::Cursor& cursor, sk::oci::bind::Data& data) const
{
  getScope().notice(SK_METHOD) << "in";
}

sk::oci::bind::out& 
sk::oci::bind::out::
operator<<(const sk::oci::Integers& values)
{
  getScope().notice(SK_METHOD) << "Integers";
  return *this;
}

sk::oci::bind::out& 
sk::oci::bind::out::
operator<<(const sk::oci::Strings& values)
{
  getScope().notice(SK_METHOD) << "Strings";
  return *this;
}

