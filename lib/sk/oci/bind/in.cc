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
#include <sk/util/ArrayList.cxx>

#include <sk/oci/bind/in.h>
#include "TaggedPlace.h"
#include "PositionalPlace.h"

#include <sk/oci/Integers.h>
#include <sk/oci/Strings.h>

static const sk::util::String __className("sk::oci::bind::in");

struct sk::oci::bind::in::Data : public virtual sk::util::Object {
  Data()
    : cardinality(0) {}

  sk::util::ArrayList<sk::oci::bind::Place> places;
  sk::util::Holder<sk::oci::bind::Place> cooker;
  int cardinality;
};

sk::oci::bind::in::
in()
  : _dataHolder(new in::Data()), _data(_dataHolder.getMutable())
{
}

sk::oci::bind::in::
~in()
{
}

const sk::util::Class
sk::oci::bind::in::
getClass() const
{
  return sk::util::Class(__className);
}

namespace {
  struct InputBinder : public virtual sk::util::Processor<const sk::oci::bind::Place> {
    InputBinder(sk::oci::Statement& statement)
      : _statement(statement) {}

    void process(const sk::oci::bind::Place& place) const {
      place.bind(_statement);
    }
    sk::oci::Statement& _statement;
  };
}

void 
sk::oci::bind::in::
prepareStatement(sk::oci::Statement& statement) const
{
  if(_data.cooker.isEmpty() == false) {
    throw sk::util::IllegalStateException("Incomplete data specification");
  }
  if(_data.cardinality == 0) {
    return;
  }
  statement.setCapacity(_data.cardinality);
  _data.places.forEach(InputBinder(statement));
}

void 
sk::oci::bind::in::
processCursor(sk::oci::Cursor& cursor, sk::oci::bind::Data& data) const
{
}

void
sk::oci::bind::in::
analyzeCardinality(int cardinality)
{
  if(cardinality <= 0) {
    throw sk::util::IllegalStateException("Wrong cardinality");
  }
  if(_data.cardinality == 0) {
    _data.cardinality = cardinality;
  }
  else if(_data.cardinality != cardinality) {
    throw sk::util::IllegalStateException("Mismatched cardinality");
  }
}

sk::oci::bind::in& 
sk::oci::bind::in::
operator<<(const sk::oci::Integers& data)
{
  if(_data.cooker.isEmpty() == true) {
    throw sk::util::IllegalStateException(SK_METHOD);
  }
  analyzeCardinality(data.size());
  _data.cooker.getMutable().setValue(new sk::oci::Integers(data));
  _data.places.add(_data.cooker.deprive());

  return *this;
}

sk::oci::bind::in& 
sk::oci::bind::in::
operator<<(const sk::oci::Strings& data)
{
  if(_data.cooker.isEmpty() == true) {
    throw sk::util::IllegalStateException(SK_METHOD);
  }
  analyzeCardinality(data.size());
  _data.cooker.getMutable().setValue(new sk::oci::Strings(data));
  _data.places.add(_data.cooker.deprive());

  return *this;
}

sk::oci::bind::in& 
sk::oci::bind::in::
operator<<(const sk::util::String& tag)
{
  if(_data.cooker.isEmpty() == true) {
    _data.cooker.set(new TaggedPlace(tag));
  }
  else {
    (*this) << (sk::oci::Strings() << tag);
  }
  return *this;
}

sk::oci::bind::in& 
sk::oci::bind::in::
operator<<(int position)
{
  if(_data.cooker.isEmpty() == true) {
    _data.cooker.set(new PositionalPlace(position));
  }
  else {
    (*this) << (sk::oci::Integers() << position);
  }
  return *this;
}

sk::oci::bind::in& 
sk::oci::bind::in::
operator<<(const char* tag)
{
  return (*this) << sk::util::String(tag);
}

