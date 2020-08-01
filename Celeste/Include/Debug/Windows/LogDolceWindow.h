#pragma once

#include "Dolce/DolceWindow.h"
#include "spdlog/common.h"

#include <vector>
#include <memory>
#include <bitset>


namespace Celeste::Debug
{
  class DolceSink_st;

  class LogDolceWindow : public Dolce::DolceWindow
  {
    public:
      LogDolceWindow();
      ~LogDolceWindow() override;

      void render() override;

    private:
      void clearLog();
      void renderLogLine(const std::tuple<spdlog::level::level_enum, std::string>& logLine);
      void renderLogFlag(const char* label, spdlog::level::level_enum level);

      std::shared_ptr<DolceSink_st> m_dolceLogSink;
      std::bitset<spdlog::level::level_enum::n_levels> m_logFlags;
  };
}