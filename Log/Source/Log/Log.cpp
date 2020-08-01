#include "Log/Log.h"
#include "spdlog/sinks/basic_file_sink.h"


namespace Celeste::Log
{
  //------------------------------------------------------------------------------------------------
  void addSink(spdlog::sink_ptr sink)
  {
    spdlog::default_logger()->sinks().emplace_back(sink);
  }

  //------------------------------------------------------------------------------------------------
  void addFileSink(const std::string& logFilePath)
  {
    addSink(std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath));
  }

  //------------------------------------------------------------------------------------------------
  void removeSink(spdlog::sink_ptr sink)
  {
    auto& sinks = spdlog::default_logger()->sinks();
    auto sinkIt = std::remove(sinks.begin(), sinks.end(), sink);

    if (sinkIt != sinks.end())
    {
      sinks.erase(sinkIt);
    }
  }

  //------------------------------------------------------------------------------------------------
  void flush()
  {
    spdlog::default_logger()->flush();
  }
}