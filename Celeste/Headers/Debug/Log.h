#pragma once

#include "Debug/Logging/ILogger.h"

#include <memory>

#ifdef _DEBUG
#define BASIC_LOG(message, verbosity) Celeste::Log::getLogger()->log(message, verbosity, FUNCTION, FILENAME, LINE);
#else
#define BASIC_LOG(message, verbosity)
#endif

#ifdef _DEBUG
#define LOG(message) BASIC_LOG(message, Celeste::ILogger::Verbosity::kRaw)
#else
#define LOG(message)
#endif

#ifdef _DEBUG
#define LOG_INFO(message) BASIC_LOG(message, Celeste::ILogger::Verbosity::kInfo)
#else
#define LOG_INFO(message)
#endif

#ifdef _DEBUG
#define LOG_WARNING(message) BASIC_LOG(message, Celeste::ILogger::Verbosity::kWarning)
#else
#define LOG_WARNING(message)
#endif

#ifdef _DEBUG
#define LOG_ERROR(message) BASIC_LOG(message, Celeste::ILogger::Verbosity::kError)
#else
#define LOG_ERROR(message)
#endif

#ifdef _DEBUG
#define LOG_CRITICAL_ERROR(message) BASIC_LOG(message, Celeste::ILogger::Verbosity::kCriticalError)
#else
#define LOG_CRITICAL_ERROR(message)
#endif

namespace Celeste
{
  class Log
  {
    public:
      Log(const Log&) = delete;
      Log(Log&&) = delete;
      void operator=(const Log&) = delete;

      CelesteDllExport static void setLogger(ILogger* asserter);
      CelesteDllExport static ILogger* getLogger();

    private:
      Log();
      static Log& instance();

      static std::unique_ptr<ILogger> m_logger;
  };
}