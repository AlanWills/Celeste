#pragma once

#include "Debug/Asserting/IAsserter.h"


namespace Celeste
{
  /// Assert class designed to not do any debug checking - useful for when we wish to temporarily disable asserts in tests for example
  class NullAsserter : public IAsserter
  {
    public:
      NullAsserter() = default;
      ~NullAsserter() override = default;

      /// \brief No-op check function
      inline void check(bool condition) const override { }
  };
};