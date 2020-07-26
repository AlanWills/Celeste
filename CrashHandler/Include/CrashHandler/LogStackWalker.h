#pragma once

#include "StackWalker/StackWalker.h"


namespace CrashHandler
{
  class LogStackWalker : public StackWalker
  {
    protected:
      void OnOutput(LPCSTR szText) override;
  };
}