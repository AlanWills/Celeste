#pragma once

#include "Log/ILogger.h"
#include "CelesteStl/Templates/Unused.h"

#include <memory>

#ifdef _DEBUG
#define BASIC_LOG(message, verbosity) Celeste::Log::Logging::getLogger().log(message, verbosity, FUNCTION, FILENAME, LINE);
#else
#define BASIC_LOG(message, verbosity) celstl::unused(message); celstl::unused(verbosity);
#endif

#ifdef _DEBUG
#define LOG(message) BASIC_LOG(message, Celeste::Log::Verbosity::kRaw)
#else
#define LOG(message) celstl::unused(message);
#endif

#ifdef _DEBUG
#define LOG_INFO(message) BASIC_LOG(message, Celeste::Log::Verbosity::kInfo)
#else
#define LOG_INFO(message) celstl::unused(message);
#endif

#ifdef _DEBUG
#define LOG_WARNING(message) BASIC_LOG(message, Celeste::Log::Verbosity::kWarning)
#else
#define LOG_WARNING(message) celstl::unused(message);
#endif

#ifdef _DEBUG
#define LOG_ERROR(message) BASIC_LOG(message, Celeste::Log::Verbosity::kError)
#else
#define LOG_ERROR(message) celstl::unused(message);
#endif

#ifdef _DEBUG
#define LOG_CRITICAL_ERROR(message) BASIC_LOG(message, Celeste::Log::Verbosity::kCriticalError)
#else
#define LOG_CRITICAL_ERROR(message) celstl::unused(message);
#endif

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