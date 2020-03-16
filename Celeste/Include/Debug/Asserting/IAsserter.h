#pragma once

#include "CelesteDllExport.h"


namespace Celeste
{
  class CelesteDllExport IAsserter
  {
    public:
      virtual ~IAsserter() {}

      virtual void check(bool condition) const = 0;
  };
}