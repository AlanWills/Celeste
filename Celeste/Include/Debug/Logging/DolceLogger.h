#pragma once

#include "FileLogger.h"
#include "CelesteStl/Memory/ObserverPtr.h"


namespace Celeste::Debug
{
  class LogDolceWindow;
}

namespace Celeste::Log
{
  class DolceLogger : public FileLogger
  {
    public:
      CelesteDllExport DolceLogger(Celeste::Debug::LogDolceWindow& logWindow, const std::string& logFileFullPath);
      CelesteDllExport DolceLogger(Celeste::Debug::LogDolceWindow& logWindow, const Path& logFilePath) :
        DolceLogger(logWindow, logFilePath.as_string()) { }
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