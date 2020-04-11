#pragma once

#include "FileLogger.h"
#include "Memory/ObserverPtr.h"


namespace Dolce
{
  class Dolce;
}

namespace Celeste::Debug
{
  class LogDolceWindow;
}

namespace Celeste::Log
{
  class DolceLogger : public FileLogger
  {
    public:
      CelesteDllExport DolceLogger(Dolce::Dolce& dolce, const std::string& logFileFullPath);
      CelesteDllExport DolceLogger(Dolce::Dolce& dolce, const Path& logFilePath) :
        DolceLogger(dolce, logFilePath.as_string()) { }
      CelesteDllExport ~DolceLogger();

      CelesteDllExport void log(
        const std::string& message, 
        Verbosity verbosity, 
        const char* function, 
        const char* file, 
        int line) override;

    private:
      using Inherited = FileLogger;

      observer_ptr<Debug::LogDolceWindow> m_logWindow;
  };
}