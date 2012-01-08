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
#include <sk/util/Vector.cxx>

#include <sk/oci/bind/out.h>
#include <sk/oci/Value.h>
#include <sk/oci/Data.h>

static const sk::util::String __className("sk::oci::bind::out");

struct sk::oci::bind::out::Data : public virtual sk::util::Object {
  Data(int amount, int skip)
    : amount(std::max(0, amount)), skip(std::max(0, skip)) {}

  sk::util::Vector<sk::oci::Value> values;
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

namespace {
  struct OutputBinder : public virtual sk::util::Processor<const sk::oci::Value> {
    OutputBinder(sk::util::List<sk::oci::Data>& bounds, sk::oci::Cursor& cursor)
      : _bounds(bounds), _cursor(cursor), _position(0) {}

    void process(const sk::oci::Value& value) const {
      _bounds.add(_cursor.boundData(value.bindPosition(++_position, _cursor)));
    }
    sk::util::List<sk::oci::Data>& _bounds;
    sk::oci::Cursor& _cursor;
    mutable int _position;
  };

  struct Populator : public virtual sk::util::Processor<sk::oci::Value> {
    Populator(sk::util::Vector<sk::oci::Data>& bounds, int amount)
      : _bounds(bounds), _amount(amount), _position(0) {}

    void process(sk::oci::Value& value) const {
      const sk::oci::Data& bind = _bounds.get(_position++);
      for(int index; index < _amount; ++index) {
        value.assume(bind.piece(index));
      }
    }
    sk::util::Vector<sk::oci::Data>& _bounds;
    const int _amount;
    mutable int _position;
  };
}

void
sk::oci::bind::out::
processCursor(sk::oci::Cursor& cursor, sk::oci::bind::Data& data) const
{
  cursor.setCapacity(_data.amount);
  sk::util::Vector<sk::oci::Data> bounds;
  _data.values.forEach(OutputBinder(bounds, cursor));

  for(uint32_t rows=cursor.fetch(); rows != 0; rows=cursor.fetch()) {
    _data.values.forEach(Populator(bounds, _data.amount));
  }
}

sk::oci::bind::out&
sk::oci::bind::out::
operator<<(const sk::oci::Integers& values)
{
  _data.values.add(values);
  return *this;
}

sk::oci::bind::out&
sk::oci::bind::out::
operator<<(const sk::oci::Strings& values)
{
  _data.values.add(values);
  return *this;
}

