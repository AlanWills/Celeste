#pragma once

#include "Assert/IAsserter.h"


namespace Celeste
{
  class DebugAsserter : public IAsserter
  {
    public:
      DebugAsserter() = default;
      ~DebugAsserter() override = default;

      void check(bool condition) const override;
  };
}