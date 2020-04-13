#pragma once

#include "Log/ILogger.h"

#include <functional>


namespace TestLog
{
  class MockLogger : public Celeste::Log::ILogger
  {
    public:
      ~MockLogger() override = default;

      void log(
        const std::string& message, 
        Celeste::Log::Verbosity verbosity, 
        const char* /*function*/, 
        const char* /*file*/, 
        int /*line*/) override
      {
        if (m_onLogCalled)
        {
          m_onLogCalled(message, verbosity);
        }
      }

      void flush() override {}
      void clear() override {}

      std::function<void(const std::string&, Celeste::Log::Verbosity)> m_onLogCalled;
  };
}