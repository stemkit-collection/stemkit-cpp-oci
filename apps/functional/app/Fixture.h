/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _APP_FIXTURE_H_
#define _APP_FIXTURE_H_

#include <sk/util/Object.h>

namespace app {
  class Fixture
    : public virtual sk::util::Object
  {
    public:
      virtual sk::oci::Accessor& dbAccessor() = 0;
      virtual const sk::util::String testTable() const = 0;

      virtual void dropTestTable() = 0;
      virtual void createTestTable(const sk::util::String& content) = 0;
      virtual void truncateTestTable() = 0;

      virtual const sk::util::String user() const = 0;
      virtual const sk::util::String password() const = 0;
      virtual const sk::util::String sid() const = 0;
  };
}

#endif /* _APP_FIXTURE_H_ */
