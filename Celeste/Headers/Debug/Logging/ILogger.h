#pragma once

#include "CelesteDllExport.h"
#include <string>


namespace Celeste
{
  #define FUNCTION __func__
  #define FILENAME __FILE__
  #define LINE __LINE__

  class CelesteDllExport ILogger
  {
    public:
      enum Verbosity
      {
        kRaw = 1 << 0, // Straight up text that will not be decorated
        kInfo = 1 << 1, // General information
        kWarning = 1 << 2,  // Warnings are failures that should be fixed but the game can still run
        kError = 1 << 3,    // Errors constitute more serious problems that should be fixed immediately - the game may or may not be able to continue running
        kCriticalError = 1 << 4,  // Critical errors correspond to crashes
      };

      virtual ~ILogger() {}

      virtual void log(const std::string& message, Verbosity verbosity, const char* function, const char* file, int line) = 0;
      virtual void flush() = 0;
      virtual void clear() = 0;

      virtual const std::string& getLog() = 0;
  };
}