#include "Debug/Windows/LogDolceWindow.h"
#include "Assert/Assert.h"


namespace Celeste::Debug
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    std::string getVerbosityString(Log::Verbosity verbosity)
    {
      switch (verbosity)
      {
      case Log::Verbosity::kInfo:
        return "INFO";

      case Log::Verbosity::kWarning:
        return "WARNING";

      case Log::Verbosity::kError:
        return "ERROR";

      case Log::Verbosity::kCriticalError:
        return "CRITICAL ERROR";

      case Log::Verbosity::kRaw:
        return "";

      default:
        ASSERT_FAIL();
        return "";
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  LogDolceWindow::LogDolceWindow() :
    DolceWindow("Log")
  {
  }

  //------------------------------------------------------------------------------------------------
  void LogDolceWindow::render()
  {
    for (const auto& logLine : m_logLines)
    {
      renderLogLine(logLine);
    }
  }

  //------------------------------------------------------------------------------------------------
  void LogDolceWindow::renderLogLine(const std::tuple<Log::Verbosity, std::string>& logLine)
  {
    ImGui::Text(std::get<1>(logLine).c_str());
  }

  //------------------------------------------------------------------------------------------------
  void LogDolceWindow::log(
    const std::string& message,
    Log::Verbosity verbosity,
    const char* function,
    const char* file,
    int line)
  {
    std::string logLine;

    if (verbosity != Log::Verbosity::kRaw)
    {
      logLine.append(Internals::getVerbosityString(verbosity));
      logLine.append(": '");
    }

    logLine.append(message);
    logLine.append("' in ");
    logLine.append(function);
    logLine.append(", line ");
    logLine.append(std::to_string(line));
    logLine.append(", file ");
    logLine.append(file);

    m_logLines.emplace_back(verbosity, logLine);
  }
}