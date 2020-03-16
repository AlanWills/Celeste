#pragma once

#include "CelesteDllExport.h"
#include "Debug/Asserting/IAsserter.h"


namespace Celeste
{
  class DebugAsserter : public IAsserter
  {
    public:
      DebugAsserter() = default;
      ~DebugAsserter() override = default;

      /// Will check the inputted condition and raise a runtime assert if the condition was false
      CelesteDllExport void check(bool condition) const override;
  };
}