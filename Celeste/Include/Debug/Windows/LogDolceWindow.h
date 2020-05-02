#pragma once

#include "Dolce/DolceWindow.h"
#include "Log/Verbosity.h"

#include <vector>


namespace Celeste::Debug
{
  class LogDolceWindow : public Dolce::DolceWindow
  {
    public:
      LogDolceWindow();
      ~LogDolceWindow() override = default;

      void render() override;

      void log(
        const std::string& message,
        Log::Verbosity verbosity,
        const char* function,
        const char* file,
        int line);

    private:
      void toggleLogFlag(Log::Verbosity verbosity);

      void clearLog();

      void renderLogFlag(const char* label, Log::Verbosity verbosity);
      void renderLogLine(const std::tuple<Log::Verbosity, std::string>& logLine);

      std::vector<std::tuple<Log::Verbosity, std::string>> m_logLines;
      Log::Verbosity m_logFlags;
  };
}