/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _TEST_APP_H_
#define _TEST_APP_H_

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <sk/util/Holder.hxx>
#include <sk/rt/Scope.h>
#include <sk/oci/Accessor.h>
#include "app/Fixture.h"

namespace test {
  class App 
    : public virtual app::Fixture
  {
    public:
      App();
      virtual ~App();

      static app::Fixture& fixture();
      void setup();

      // app::Fixture implementation.
      sk::oci::Accessor& dbAccessor();
  
      // sk::util::Object re-implementation.
      const sk::util::Class getClass() const;
  
    private:
      App(const App& other);
      App& operator = (const App& other);

      const sk::util::String user() const;
      const sk::util::String password() const;
      const sk::util::String sid() const;
      const sk::util::String table() const;

      const sk::rt::Scope _scope;
      sk::util::Holder<sk::oci::Accessor> _accessorHolder;

      static sk::util::Holder<App> _appHolder;
  };
}

#endif /* _TEST_APP_H_ */
