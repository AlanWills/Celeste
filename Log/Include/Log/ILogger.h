#pragma once

#include "LogDllExport.h"
#include "Verbosity.h"

#include <string>


namespace Celeste::Log
{
  #define FUNCTION __func__
  #define FILENAME __FILE__
  #define LINE __LINE__

  class ILogger
  {
    public:
      virtual ~ILogger() {}

      LogDllExport virtual void log(const std::string& message, Verbosity verbosity, const char* function, const char* file, int line) = 0;
      LogDllExport virtual void flush() = 0;
      LogDllExport virtual void clear() = 0;
  };
}