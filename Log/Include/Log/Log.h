#pragma once

#include "LogDllExport.h"
#include "spdlog/spdlog.h"

#include <memory>
#include <string>


namespace Celeste::Log
{
  LogDllExport void addSink(spdlog::sink_ptr sink);
  LogDllExport void addFileSink(const std::string& logFilePath);

  LogDllExport void removeSink(spdlog::sink_ptr sink);

  LogDllExport void flush();

  template<typename FormatString, typename... Args>
  inline void log(spdlog::source_loc source, spdlog::level::level_enum lvl, const FormatString& fmt, const Args&... args)
  {
    spdlog::log(source, lvl, fmt, args...);
  }

  template<typename FormatString, typename... Args>
  inline void log(spdlog::level::level_enum lvl, const FormatString& fmt, const Args&... args)
  {
    spdlog::log(spdlog::source_loc{}, lvl, fmt, args...);
  }

  template<typename FormatString, typename... Args>
  inline void trace(const FormatString& fmt, const Args&... args)
  {
    spdlog::trace(fmt, args...);
  }

  template<typename FormatString, typename... Args>
  inline void debug(const FormatString& fmt, const Args&... args)
  {
    spdlog::debug(fmt, args...);
  }

  template<typename FormatString, typename... Args>
  inline void info(const FormatString& fmt, const Args&... args)
  {
    spdlog::info(fmt, args...);
  }

  template<typename FormatString, typename... Args>
  inline void warn(const FormatString& fmt, const Args&... args)
  {
    spdlog::warn(fmt, args...);
  }

  template<typename FormatString, typename... Args>
  inline void error(const FormatString& fmt, const Args&... args)
  {
    spdlog::error(fmt, args...);
  }

  template<typename FormatString, typename... Args>
  inline void critical(const FormatString& fmt, const Args&... args)
  {
    spdlog::critical(fmt, args...);
  }

  template<typename T>
  inline void log(spdlog::source_loc source, spdlog::level::level_enum lvl, const T& msg)
  {
    spdlog::log(source, lvl, msg);
  }

  template<typename T>
  inline void log(spdlog::level::level_enum lvl, const T& msg)
  {
    spdlog::log(lvl, msg);
  }

  template<typename T>
  inline void trace(const T& msg)
  {
    spdlog::trace(msg);
  }

  template<typename T>
  inline void debug(const T& msg)
  {
    spdlog::debug(msg);
  }

  template<typename T>
  inline void info(const T& msg)
  {
    spdlog::info(msg);
  }

  template<typename T>
  inline void warn(const T& msg)
  {
    spdlog::warn(msg);
  }

  template<typename T>
  inline void error(const T& msg)
  {
    spdlog::error(msg);
  }

  template<typename T>
  inline void critical(const T& msg)
  {
    spdlog::critical(msg);
  }
}