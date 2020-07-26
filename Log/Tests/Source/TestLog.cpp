#include "TestUtils/TestUtils.h"

#include "Log/Log.h"
#include "FileSystem/Path.h"
#include "FileSystem/Directory.h"

#include "Mocks/Log/MockLogger.h"

#include <chrono>
#include <thread>

using namespace Celeste;
using namespace Celeste::Log;


namespace TestLog
{
  static Path logFilePath(Directory::getExecutingAppDirectory(), "Log.txt");

  BASE_TEST_CLASS(TestLog)
    
  //------------------------------------------------------------------------------------------------
  void TestLog::testInitialize()
  {
    Logging::setLogger(std::make_unique<MockLogger>());
  }

  //------------------------------------------------------------------------------------------------
  MockLogger& TestLog::getMockLogger()
  {
    return static_cast<MockLogger&>(Logging::getLogger());
  }

#pragma region Macro Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Log_LOG_Macro_LogsMessageCorrectly)
  {
    getMockLogger().m_onLogCalled = [](const std::string& message, Verbosity verbosity)
    {
      Assert::AreEqual("Test", message.c_str());
      Assert::IsTrue(Verbosity::kRaw == verbosity);
    };

    LOG("Test");
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Log_LOG_INFO_Macro_LogsMessageCorrectly)
  {
    int line = LINE;
    LOG_INFO("Test");

    getMockLogger().m_onLogCalled = [&line](const std::string& message, Verbosity verbosity)
    {
      std::string expected("Info: \"Test\" in function: Log_LOG_INFO_Macro_LogsMessageCorrectly, in file: ");
      expected.append(FILENAME);
      expected.append(", on line: ");
      expected.append(std::to_string(line + 1));
      expected.append("\n");

      Assert::AreEqual(expected, message);
      Assert::IsTrue(Verbosity::kInfo == verbosity);
    };
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Log_LOG_WARNING_Macro_LogsWarningCorrectly)
  {
    int line = LINE;
    LOG_WARNING("Test");

    getMockLogger().m_onLogCalled = [&line](const std::string& message, Verbosity verbosity)
    {
      std::string expected("Warning: \"Test\" in function: Log_LOG_WARNING_Macro_LogsWarningCorrectly, in file: ");
      expected.append(FILENAME);
      expected.append(", on line: ");
      expected.append(std::to_string(line + 1));
      expected.append("\n");

      Assert::AreEqual(expected, message);
      Assert::IsTrue(Verbosity::kInfo == verbosity);
    };
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Log_LOG_ERROR_Macro_LogsErrorCorrectly)
  {
    int line = LINE;
    LOG_ERROR("Test");

    getMockLogger().m_onLogCalled = [&line](const std::string& message, Verbosity verbosity)
    {
      std::string expected("Error: \"Test\" in function: Log_LOG_ERROR_Macro_LogsErrorCorrectly, in file: ");
      expected.append(FILENAME);
      expected.append(", on line: ");
      expected.append(std::to_string(line + 1));
      expected.append("\n");

      Assert::AreEqual(expected, message);
      Assert::IsTrue(Verbosity::kInfo == verbosity);
    };
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Log_LOG_CRITICAL_ERROR_Macro_LogsCriticalErrorCorrectly)
  {
    int line = LINE;
    LOG_CRITICAL_ERROR("Test");

    getMockLogger().m_onLogCalled = [&line](const std::string& message, Verbosity verbosity)
    {
      std::string expected("Critical Error: \"Test\" in function: Log_LOG_CRITICAL_ERROR_Macro_LogsCriticalErrorCorrectly, in file: ");
      expected.append(FILENAME);
      expected.append(", on line: ");
      expected.append(std::to_string(line + 1));
      expected.append("\n");

      Assert::AreEqual(expected, message);
      Assert::IsTrue(Verbosity::kInfo == verbosity);
    };
  }

#pragma endregion

  };
}