#include "UtilityHeaders/UnitTestHeaders.h"

#include "Debug/Logging/FileLogger.h"
#include "FileSystem/Path.h"
#include "FileSystem/Directory.h"
#include "FileAssert.h"

// There is ambiguity in naming with the unit test logger here
// So we qualify with namespaces

using namespace Celeste;
using namespace Celeste::Log;


namespace TestCeleste
{
  static Path logFilePath(Directory::getExecutingAppDirectory(), "Log.txt");

  std::string getString(Verbosity verbosity)
  {
    switch (verbosity)
    {
    case Verbosity::kInfo:
        return "Info";

      case Verbosity::kWarning:
        return "Warning";

      case Verbosity::kError:
        return "Error";

      case Verbosity::kCriticalError:
        return "Critical Error";

      default:
        return "";
    }
  }

  std::string getLogString(
    Verbosity verbosity,
    const std::string& message,
    int line,
    const std::string& function,
    const std::string& filename)
  {
    std::string expected(getString(verbosity));
    expected.append(": ");
    expected.append(message);
    expected.append(" in function: ");
    expected.append(function);
    expected.append(", in file: ");
    expected.append(filename);
    expected.append(", on line: ");
    expected.append(std::to_string(line));
    
    return expected;
  }

  CELESTE_TEST_CLASS(TestFileLogger)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileLogger_ConstructorWithString_CreatesOrClearsLogFile)
  {
    // Sanity check to catch any errors in constructor and make sure the log file is cleared
    FileLogger logger(logFilePath.as_string());

    checkLogFile("");
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileLogger_ConstructorWithPath_CreatesOrClearsLogFile)
  {
    // Sanity check to catch any errors in constructor and make sure the log file is cleared
    FileLogger logger(logFilePath);

    checkLogFile("");
  }

#pragma endregion

#pragma region Log Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileLogger_LogRaw)
  {
    std::string message("Simple Log");
    FileLogger logger(logFilePath);

    int line = __LINE__;
    logger.log(message, Verbosity::kRaw, FUNCTION, FILENAME, line);
    logger.flush();

    Assert::AreEqual(message + "\n", logger.getLog());

    checkLogFile(message);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileLogger_LogInfo)
  {
    std::string message("Simple Log");
    FileLogger logger(logFilePath);

    int line = LINE;
    logger.log(message, Verbosity::kInfo, FUNCTION, FILENAME, line);
    logger.flush();

    std::string expected = getLogString(Verbosity::kInfo, message, line, FUNCTION, FILENAME);

    Assert::AreEqual(expected + "\n", logger.getLog());

    checkLogFile(expected);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileLogger_LogWarning)
  {
    std::string message("Message");

    FileLogger logger(logFilePath);
    int line = LINE;
    logger.log(message, Verbosity::kWarning, FUNCTION, FILENAME, line);
    logger.flush();

    std::string expected = getLogString(Verbosity::kWarning, message, line, FUNCTION, FILENAME);

    Assert::AreEqual(expected + "\n", logger.getLog());

    checkLogFile(expected);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileLogger_LogError)
  {
    std::string message("Message");

    FileLogger logger(logFilePath);
    int line = LINE;
    logger.log(message, Verbosity::kError, FUNCTION, FILENAME, line);
    logger.flush();

    std::string expected = getLogString(Verbosity::kError, message, line, FUNCTION, FILENAME);

    Assert::AreEqual(expected + "\n", logger.getLog());

    checkLogFile(expected);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileLogger_LogCriticalError)
  {
    std::string message("Message");

    FileLogger logger(logFilePath);
    int line = LINE;
    logger.log(message, Verbosity::kCriticalError, FUNCTION, FILENAME, line);
    logger.flush();

    std::string expected = getLogString(Verbosity::kCriticalError, message, line, FUNCTION, FILENAME);

    Assert::AreEqual(expected + "\n", logger.getLog());

    checkLogFile(expected);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileLogger_LogMultipleMessages)
  {
    std::string message("Simple Log");

    FileLogger logger(logFilePath);
    int line = LINE;

    logger.log(message, Verbosity::kInfo, FUNCTION, FILENAME, line);
    logger.log(message, Verbosity::kInfo, FUNCTION, FILENAME, line + 1);
    logger.log(message, Verbosity::kInfo, FUNCTION, FILENAME, line + 2);
    logger.flush();

    std::string expected = getLogString(Verbosity::kInfo, message, line, FUNCTION, FILENAME);
    expected.push_back('\n');
    expected.append(getLogString(Verbosity::kInfo, message, line + 1, FUNCTION, FILENAME));
    expected.push_back('\n');
    expected.append(getLogString(Verbosity::kInfo, message, line + 2, FUNCTION, FILENAME));

    Assert::AreEqual(expected + "\n", logger.getLog());

    checkLogFile(expected);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileLogger_FlushingDuringWriting_WritesBackBuffer_AndSwapsBuffers)
  {
    std::string message;
    for (size_t i = 0; i < (size_t)(LOGGER_BUFFER_SIZE * 0.35f); ++i)
    {
      message.append("S");
    }

    FileLogger logger(logFilePath);
    int line = LINE;

    logger.log(message, Verbosity::kInfo, FUNCTION, FILENAME, line);
    logger.log(message, Verbosity::kInfo, FUNCTION, FILENAME, line + 1);

    // Logger will flush when writing this message
    logger.log(message, Verbosity::kInfo, FUNCTION, FILENAME, line + 2);

    std::string expected = getLogString(Verbosity::kInfo, message, line, FUNCTION, FILENAME);
    expected.push_back('\n');
    expected.append(getLogString(Verbosity::kInfo, message, line + 1, FUNCTION, FILENAME));

    // The first two messages will be in the log back buffer
    Assert::AreEqual(expected + "\n", logger.getLog());

    checkLogFile(expected);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileLogger_Log_ShouldFlushAfterEveryLog_WritesToFileWithEveryMessage)
  {
    // Non flushing behaviour
    {
      FileLogger nonFlushingLogger(logFilePath);
      nonFlushingLogger.shouldFlushAfterEveryLog(false);

      nonFlushingLogger.log("Test", Verbosity::kInfo, FUNCTION, FILENAME, LINE);
      nonFlushingLogger.log("Non Flushing", Verbosity::kInfo, FUNCTION, FILENAME, LINE);
      nonFlushingLogger.log("Logger", Verbosity::kInfo, FUNCTION, FILENAME, LINE);

      checkLogFile("");
    }

    // Flushing behaviour for comparison
    {
      FileLogger flushingLogger(logFilePath);
      flushingLogger.shouldFlushAfterEveryLog(true);

      int line = LINE;

      flushingLogger.log("Test", Verbosity::kInfo, FUNCTION, FILENAME, line);
      flushingLogger.log("Flushing", Verbosity::kInfo, FUNCTION, FILENAME, line + 1);
      flushingLogger.log("Logger", Verbosity::kInfo, FUNCTION, FILENAME, line + 2);

      std::string expected = getLogString(Verbosity::kInfo, "Test", line, FUNCTION, FILENAME);
      expected.push_back('\n');
      expected.append(getLogString(Verbosity::kInfo, "Flushing", line + 1, FUNCTION, FILENAME));
      expected.push_back('\n');
      expected.append(getLogString(Verbosity::kInfo, "Logger", line + 2, FUNCTION, FILENAME));

      checkLogFile(expected);
    }
  }

#pragma endregion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileLogger_Destructor_WritesBothBuffersToFile)
  {
    int line = LINE;
    std::string function = FUNCTION;
    std::string filename = FILENAME;

    std::string expected = getLogString(Verbosity::kInfo, "Test", line, function, filename);

    // Scope the logger so it is destroyed in this section of the test rather than at the end of the function
    // This is to trigger the destructor
    {
      FileLogger logger(logFilePath);
      logger.log("Test", Verbosity::kInfo, FUNCTION, FILENAME, line);
    }

    checkLogFile(expected);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FileLogger_Clear_ClearsBothBuffersAndLogFile)
  {
    FileLogger logger(logFilePath);
    logger.log("Just logging something", Verbosity::kInfo, FUNCTION, FILENAME, LINE);
    logger.flush();

    Assert::IsFalse(logger.getLog().empty());

    std::string logFileContents;
    File(logFilePath).read(logFileContents);
    Assert::IsFalse(logFileContents.empty());

    logger.clear();

    Assert::IsTrue(logger.getLog().empty());

    logFileContents.clear();
    File(logFilePath).read(logFileContents);
    Assert::IsTrue(logFileContents.empty());
  }

  //------------------------------------------------------------------------------------------------
  void checkLogFile(const std::string& logFileContents)
  {
    FileAssert::FileContentsEqual(logFilePath.as_string(), logFileContents);
  }

  };
}