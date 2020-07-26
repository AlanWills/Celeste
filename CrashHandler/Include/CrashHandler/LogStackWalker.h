#pragma once

#include "CrashHandler/StackWalker.h"


namespace CrashHandler
{
  class LogStackWalker : public StackWalker
  {
    protected:
      void OnOutput(LPCSTR szText) override;
  };
}