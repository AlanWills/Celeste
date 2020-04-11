#include "Debug/Logging/DolceLogger.h"
#include "Debug/Windows/LogDolceWindow.h"


namespace Celeste::Log
{
  //------------------------------------------------------------------------------------------------
  DolceLogger::DolceLogger(Celeste::Debug::LogDolceWindow& logWindow, const std::string& logFileFullPath) :
    FileLogger(logFileFullPath),
    m_logWindow(&logWindow)
  {
  }

  //------------------------------------------------------------------------------------------------
  DolceLogger::~DolceLogger() = default;

  //------------------------------------------------------------------------------------------------
  void DolceLogger::log(
    const std::string& message,
    Verbosity verbosity,
    const char* function,
    const char* file,
    int line)
  {
    Inherited::log(message, verbosity, function, file, line);

    m_logWindow->log(message, verbosity, function, file, line);
  }
}