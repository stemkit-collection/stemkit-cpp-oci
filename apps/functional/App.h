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

namespace test {
  class App 
    : public virtual sk::util::Object
  {
    public:
      App(const sk::util::String& config);
      virtual ~App();

      void setup();
  
      // sk::util::Object re-implementation.
      const sk::util::Class getClass() const;
  
    private:
      App(const App& other);
      App& operator = (const App& other);
  };
}

#endif /* _TEST_APP_H_ */
