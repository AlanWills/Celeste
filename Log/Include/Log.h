#pragma once

#include "Logging/ILogger.h"
#include "Templates/Unused.h"

#include <memory>

#ifdef _DEBUG
#define BASIC_LOG(message, verbosity) Celeste::Log::getLogger().log(message, verbosity, FUNCTION, FILENAME, LINE);
#else
#define BASIC_LOG(message, verbosity) celstl::unused(message); celstl::unused(verbosity);
#endif

#ifdef _DEBUG
#define LOG(message) BASIC_LOG(message, Celeste::ILogger::Verbosity::kRaw)
#else
#define LOG(message) celstl::unused(message);
#endif

#ifdef _DEBUG
#define LOG_INFO(message) BASIC_LOG(message, Celeste::ILogger::Verbosity::kInfo)
#else
#define LOG_INFO(message) celstl::unused(message);
#endif

#ifdef _DEBUG
#define LOG_WARNING(message) BASIC_LOG(message, Celeste::ILogger::Verbosity::kWarning)
#else
#define LOG_WARNING(message) celstl::unused(message);
#endif

#ifdef _DEBUG
#define LOG_ERROR(message) BASIC_LOG(message, Celeste::ILogger::Verbosity::kError)
#else
#define LOG_ERROR(message) celstl::unused(message);
#endif

#ifdef _DEBUG
#define LOG_CRITICAL_ERROR(message) BASIC_LOG(message, Celeste::ILogger::Verbosity::kCriticalError)
#else
#define LOG_CRITICAL_ERROR(message) celstl::unused(message);
#endif

namespace Celeste
{
  class Log
  {
    public:
      Log(const Log&) = delete;
      Log(Log&&) = delete;
      void operator=(const Log&) = delete;

      LogDllExport static void setLogger(std::unique_ptr<ILogger>&& logger);
      LogDllExport static ILogger& getLogger();

    private:
      Log();
      static Log& instance();

      static std::unique_ptr<ILogger> m_logger;
  };
}