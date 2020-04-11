#pragma once

#include "Log/ILogger.h"


namespace Celeste::Log
{
  class StdoutLogger : public ILogger
  {
    public:
      void log(const std::string& message, Verbosity verbosity, const char* function, const char* file, int line) override;
      void flush() override {}
      void clear() override {}
  };
}