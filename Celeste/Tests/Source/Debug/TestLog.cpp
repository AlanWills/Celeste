#include "UtilityHeaders/UnitTestHeaders.h"

#include "Log/Log.h"
#include "FileSystem/Path.h"
#include "FileSystem/Directory.h"

#include <chrono>
#include <thread>

using namespace Celeste;


namespace TestCeleste
{
  static Path logFilePath(Directory::getExecutingAppDirectory(), "Log.txt");

  CELESTE_TEST_CLASS(TestLog)

  //------------------------------------------------------------------------------------------------
  void TestLog::testInitialize()
  {
    // Clear the log
    Log::getLogger()->clear();
  }

  //------------------------------------------------------------------------------------------------
  void TestLog::testCleanup()
  {
    // Clear the log
    Log::getLogger()->clear();
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Log_LOG_Macro_LogsMessageCorrectly)
  {
    std::string message("Test");

    LOG(message);

    Log::getLogger()->flush();
    Assert::AreEqual(message + "\n", Log::getLogger()->getLog());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Log_LOG_INFO_Macro_LogsMessageCorrectly)
  {
    std::string message("Test");

    int line = LINE;
    LOG_INFO(message);

    std::string expected("Info: ");
    expected.append(message);
    expected.append(" in function: Log_LOG_INFO_Macro_LogsMessageCorrectly, in file: ");
    expected.append(FILENAME);
    expected.append(", on line: ");
    expected.append(std::to_string(line + 1));
    expected.append("\n");

    Log::getLogger()->flush();
    Assert::AreEqual(expected, Log::getLogger()->getLog());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Log_LOG_WARNING_Macro_LogsWarningCorrectly)
  {
    std::string message("Message");

    int line = LINE;
    LOG_WARNING(message);

    std::string expected("Warning: ");
    expected.append(message);
    expected.append(" in function: Log_LOG_WARNING_Macro_LogsWarningCorrectly, in file: ");
    expected.append(FILENAME);
    expected.append(", on line: ");
    expected.append(std::to_string(line + 1));
    expected.append("\n");

    Log::getLogger()->flush();
    Assert::AreEqual(expected, Log::getLogger()->getLog());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Log_LOG_ERROR_Macro_LogsErrorCorrectly)
  {
    std::string message("Message");

    int line = LINE;
    LOG_ERROR(message);

    std::string expected("Error: ");
    expected.append(message);
    expected.append(" in function: Log_LOG_ERROR_Macro_LogsErrorCorrectly, in file: ");
    expected.append(FILENAME);
    expected.append(", on line: ");
    expected.append(std::to_string(line + 1));
    expected.append("\n");

    Log::getLogger()->flush();
    Assert::AreEqual(expected, Log::getLogger()->getLog());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Log_LOG_CRITICAL_ERROR_Macro_LogsCriticalErrorCorrectly)
  {
    std::string message("Message");

    int line = LINE;
    LOG_CRITICAL_ERROR(message);

    std::string expected("Critical Error: ");
    expected.append(message);
    expected.append(" in function: Log_LOG_CRITICAL_ERROR_Macro_LogsCriticalErrorCorrectly, in file: ");
    expected.append(FILENAME);
    expected.append(", on line: ");
    expected.append(std::to_string(line + 1));
    expected.append("\n");

    Log::getLogger()->flush();
    Assert::AreEqual(expected, Log::getLogger()->getLog());
  }

  };
}