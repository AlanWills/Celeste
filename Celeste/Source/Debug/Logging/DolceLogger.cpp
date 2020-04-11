#include "Debug/Logging/DolceLogger.h"
#include "Debug/Windows/LogDolceWindow.h"
#include "Dolce.h"


namespace Celeste::Log
{
  //------------------------------------------------------------------------------------------------
  DolceLogger::DolceLogger(Dolce::Dolce& dolce, const std::string& logFileFullPath) :
    FileLogger(logFileFullPath),
    m_logWindow(static_cast<Debug::LogDolceWindow*>(dolce.findWindow("Log")))
  {
    if (m_logWindow == nullptr)
    {
      m_logWindow = &dolce.registerWindow(std::make_unique<Debug::LogDolceWindow>());
    }

    m_logWindow->open();
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