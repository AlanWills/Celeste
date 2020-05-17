#include "Debug/Windows/LogDolceWindow.h"
#include "Assert/Assert.h"

using namespace celstl;


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

    //------------------------------------------------------------------------------------------------
    ImVec4 getVerbosityColour(Log::Verbosity verbosity)
    {
      switch (verbosity)
      {
      case Log::Verbosity::kInfo:
        return ImVec4(1, 1, 1, 1);

      case Log::Verbosity::kWarning:
        return ImVec4(1, 1, 0, 1);

      case Log::Verbosity::kError:
        return ImVec4(1, 0, 0, 1);

      case Log::Verbosity::kCriticalError:
        return ImVec4(0.25f, 0, 0, 1);

      case Log::Verbosity::kRaw:
        return ImVec4(1, 1, 1, 1);

      default:
        ASSERT_FAIL();
        return ImVec4(0, 0, 0, 0);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  LogDolceWindow::LogDolceWindow() :
    DolceWindow("Log"),
    m_logFlags(Log::Verbosity::kRaw | 
               Log::Verbosity::kInfo | 
               Log::Verbosity::kWarning | 
               Log::Verbosity::kError | 
               Log::Verbosity::kCriticalError)
  {
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
      logLine.append(": ");
    }

    logLine.append(message);
    logLine.append(" in ");
    logLine.append(function);
    logLine.append(", line ");
    logLine.append(std::to_string(line));
    logLine.append(", file ");
    logLine.append(file);

    m_logLines.emplace_back(verbosity, logLine);
  }

  //------------------------------------------------------------------------------------------------
  void LogDolceWindow::render()
  {
    renderLogFlag("Raw", Log::Verbosity::kRaw);
    
    ImGui::SameLine();
    ImGui::Spacing();
    ImGui::SameLine();

    renderLogFlag("Info", Log::Verbosity::kInfo);

    ImGui::SameLine();
    ImGui::Spacing();
    ImGui::SameLine();

    renderLogFlag("Warning", Log::Verbosity::kWarning);

    ImGui::SameLine();
    ImGui::Spacing();
    ImGui::SameLine();

    renderLogFlag("Error", Log::Verbosity::kError);

    ImGui::SameLine();
    ImGui::Spacing();
    ImGui::SameLine();

    renderLogFlag("Critical Error", Log::Verbosity::kCriticalError);

    ImGui::SameLine();
    ImGui::Spacing();
    ImGui::SameLine();
    ImGui::Spacing();
    ImGui::SameLine();

    if (ImGui::Button("Clear"))
    {
      clearLog();
    }

    ImGui::Separator();

    for (const auto& logLine : m_logLines)
    {
      if (celstl::hasFlag(m_logFlags, std::get<0>(logLine)))
      {
        renderLogLine(logLine);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void LogDolceWindow::toggleLogFlag(Log::Verbosity verbosity)
  {
    m_logFlags ^= verbosity;
  }

  //------------------------------------------------------------------------------------------------
  void LogDolceWindow::clearLog()
  {
    m_logLines.clear();
  }

  //------------------------------------------------------------------------------------------------
  void LogDolceWindow::renderLogFlag(const char* label, Log::Verbosity verbosity)
  {
    bool isFlagEnabled = celstl::hasFlag(m_logFlags, verbosity);
    if (ImGui::Checkbox(label, &isFlagEnabled))
    {
      toggleLogFlag(verbosity);
    }
  }

  //------------------------------------------------------------------------------------------------
  void LogDolceWindow::renderLogLine(const std::tuple<Log::Verbosity, std::string>& logLine)
  {
    const char* text = std::get<1>(logLine).c_str();

    ImGui::PushStyleColor(ImGuiCol_Text, Internals::getVerbosityColour(std::get<0>(logLine)));
    ImGui::Text(text);
    ImGui::PopStyleColor();
  }
}