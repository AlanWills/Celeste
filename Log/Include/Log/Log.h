#pragma once

#include "Log/ILogger.h"

#include <memory>

#define BASIC_LOG(message, verbosity) Celeste::Log::Logging::getLogger().log(message, verbosity, FUNCTION, FILENAME, LINE);
#define LOG(message) BASIC_LOG(message, Celeste::Log::Verbosity::kRaw)
#define LOG_INFO(message) BASIC_LOG(message, Celeste::Log::Verbosity::kInfo)
#define LOG_WARNING(message) BASIC_LOG(message, Celeste::Log::Verbosity::kWarning)
#define LOG_ERROR(message) BASIC_LOG(message, Celeste::Log::Verbosity::kError)
#define LOG_CRITICAL_ERROR(message) BASIC_LOG(message, Celeste::Log::Verbosity::kCriticalError)

namespace Celeste::Log
{
  class Logging
  {
    public:
      Logging(const Logging&) = delete;
      Logging(Logging&&) = delete;
      void operator=(const Logging&) = delete;

      LogDllExport static void setLogger(std::unique_ptr<ILogger>&& logger);
      LogDllExport static ILogger& getLogger();

    private:
      Logging();
      static Logging& instance();

      static std::unique_ptr<ILogger> m_logger;
  };
}