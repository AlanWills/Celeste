#pragma once

#include "AssertDllExport.h"


namespace Celeste
{
  class IAsserter
  {
    public:
      virtual ~IAsserter() {}

      AssertDllExport virtual void check(bool condition) const = 0;
  };
}