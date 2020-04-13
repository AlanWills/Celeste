#pragma once

#include "Assert/IAsserter.h"


namespace Celeste
{
  class NullAsserter : public IAsserter
  {
    public:
      NullAsserter() = default;
      ~NullAsserter() override = default;

      /// \brief No-op check function
      inline void check(bool /*condition*/) const override { }
  };
};