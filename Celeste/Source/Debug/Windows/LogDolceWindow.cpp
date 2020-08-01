#include "Debug/Windows/LogDolceWindow.h"
#include "spdlog/sinks/base_sink.h"
#include "Assert/Assert.h"
#include "Log/Log.h"

using namespace celstl;


namespace Celeste::Debug
{
  //------------------------------------------------------------------------------------------------
  class DolceSink_st : public spdlog::sinks::base_sink<spdlog::details::null_mutex>
  {
    public:
      using LogLine = std::tuple<spdlog::level::level_enum, std::string>;
      using LogLines = std::vector<LogLine>;

      const LogLines& getLogLines() const { return m_logLines; }
      void clear() { m_logLines.clear(); }

    protected:
      void sink_it_(const spdlog::details::log_msg& msg) override 
      { 
        m_logLines.emplace_back(msg.level, msg.payload.data());
      }
      void flush_() override {}

    private:
      std::vector<std::tuple<spdlog::level::level_enum, std::string>> m_logLines;
  };

  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    ImVec4 getLevelColour(spdlog::level::level_enum level)
    {
      switch (level)
      {
      case spdlog::level::level_enum::info:
        return ImVec4(1, 1, 1, 1);

      case spdlog::level::level_enum::warn:
        return ImVec4(1, 1, 0, 1);

      case spdlog::level::level_enum::err:
        return ImVec4(1, 0, 0, 1);

      case spdlog::level::level_enum::critical:
        return ImVec4(0.25f, 0, 0, 1);

      default:
        ASSERT_FAIL();
        return ImVec4(1, 1, 1, 1);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  LogDolceWindow::LogDolceWindow() :
    DolceWindow("Log"),
    m_dolceLogSink(std::make_shared<DolceSink_st>()),
    m_logFlags()
  {
    m_logFlags.set();
    Log::addSink(m_dolceLogSink);
  }

  //------------------------------------------------------------------------------------------------
  LogDolceWindow::~LogDolceWindow()
  {
    Log::removeSink(m_dolceLogSink);
  }

  //------------------------------------------------------------------------------------------------
  void LogDolceWindow::render()
  { 
    renderLogFlag("Info", spdlog::level::level_enum::info);
    
    ImGui::SameLine();
    ImGui::Spacing();
    ImGui::SameLine();
    
    renderLogFlag("Warning", spdlog::level::level_enum::warn);
    
    ImGui::SameLine();
    ImGui::Spacing();
    ImGui::SameLine();
    
    renderLogFlag("Error", spdlog::level::level_enum::err);
    
    ImGui::SameLine();
    ImGui::Spacing();
    ImGui::SameLine();
    
    renderLogFlag("Critical Error", spdlog::level::level_enum::critical);
    
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

    for (const auto& logLine : m_dolceLogSink->getLogLines())
    {
      if (m_logFlags.test(static_cast<size_t>(std::get<0>(logLine))))
      {
        renderLogLine(logLine);
      }
    }
    
    ImGui::SetScrollHere(1);
  }

  //------------------------------------------------------------------------------------------------
  void LogDolceWindow::renderLogFlag(const char* label, spdlog::level::level_enum level)
  {
    size_t levelAsSizet = static_cast<size_t>(level);
    bool isFlagEnabled = m_logFlags.test(levelAsSizet);

    if (ImGui::Checkbox(label, &isFlagEnabled))
    {
      m_logFlags.flip(levelAsSizet);
    }
  }

  //------------------------------------------------------------------------------------------------
  void LogDolceWindow::clearLog()
  {
    m_dolceLogSink->clear();
  }

  //------------------------------------------------------------------------------------------------
  void LogDolceWindow::renderLogLine(const std::tuple<spdlog::level::level_enum, std::string>& logLine)
  {
    const char* text = std::get<1>(logLine).c_str();
    
    ImGui::PushStyleColor(ImGuiCol_Text, Internals::getLevelColour(std::get<0>(logLine)));
    ImGui::Text(text);
    ImGui::PopStyleColor();
  }
}