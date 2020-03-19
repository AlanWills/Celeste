#include "UtilityHeaders/UnitTestHeaders.h"

#include "Debug/Logging/Logger.h"
#include "FileSystem/Path.h"
#include "FileSystem/Directory.h"
#include "FileAssert.h"

// There is ambiguity in naming with the unit test logger here
// So we qualify with namespaces

using namespace Celeste;


namespace TestCeleste
{
  static Path logFilePath(Directory::getExecutingAppDirectory(), "Log.txt");

  std::string getString(ILogger::Verbosity verbosity)
  {
    switch (verbosity)
    {
      case Celeste::Logger::kInfo:
        return "Info";

      case Celeste::Logger::kWarning:
        return "Warning";

      case Celeste::Logger::kError:
        return "Error";

      case Celeste::Logger::kCriticalError:
        return "Critical Error";

      default:
        return "";
    }
  }

  std::string getLogString(
    ILogger::Verbosity verbosity,
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

  CELESTE_TEST_CLASS(TestLogger)

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Logger_ConstructorWithString_CreatesOrClearsLogFile)
    {
      // Sanity check to catch any errors in constructor and make sure the log file is cleared
      Celeste::Logger logger(logFilePath.as_string());

      checkLogFile("");
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Logger_ConstructorWithPath_CreatesOrClearsLogFile)
    {
      // Sanity check to catch any errors in constructor and make sure the log file is cleared
      Celeste::Logger logger(logFilePath);

      checkLogFile("");
    }

#pragma endregion

#pragma region Log Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Logger_LogRaw)
    {
      std::string message("Simple Log");
      Celeste::Logger logger(logFilePath);

      int line = __LINE__;
      logger.log(message, ILogger::kRaw, FUNCTION, FILENAME, line);
      logger.flush();

      Assert::AreEqual(message + "\n", logger.getLog());

      checkLogFile(message);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Logger_LogInfo)
    {
      std::string message("Simple Log");
      Celeste::Logger logger(logFilePath);

      int line = LINE;
      logger.log(message, ILogger::kInfo, FUNCTION, FILENAME, line);
      logger.flush();

      std::string expected = getLogString(ILogger::kInfo, message, line, FUNCTION, FILENAME);

      Assert::AreEqual(expected + "\n", logger.getLog());

      checkLogFile(expected);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Logger_LogWarning)
    {
      std::string message("Message");

      Celeste::Logger logger(logFilePath);
      int line = LINE;
      logger.log(message, ILogger::kWarning, FUNCTION, FILENAME, line);
      logger.flush();

      std::string expected = getLogString(ILogger::kWarning, message, line, FUNCTION, FILENAME);

      Assert::AreEqual(expected + "\n", logger.getLog());

      checkLogFile(expected);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Logger_LogError)
    {
      std::string message("Message");

      Celeste::Logger logger(logFilePath);
      int line = LINE;
      logger.log(message, ILogger::kError, FUNCTION, FILENAME, line);
      logger.flush();

      std::string expected = getLogString(ILogger::kError, message, line, FUNCTION, FILENAME);

      Assert::AreEqual(expected + "\n", logger.getLog());

      checkLogFile(expected);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Logger_LogCriticalError)
    {
      std::string message("Message");

      Celeste::Logger logger(logFilePath);
      int line = LINE;
      logger.log(message, ILogger::kCriticalError, FUNCTION, FILENAME, line);
      logger.flush();

      std::string expected = getLogString(ILogger::kCriticalError, message, line, FUNCTION, FILENAME);

      Assert::AreEqual(expected + "\n", logger.getLog());

      checkLogFile(expected);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Logger_LogMultipleMessages)
    {
      std::string message("Simple Log");

      Celeste::Logger logger(logFilePath);
      int line = LINE;

      logger.log(message, ILogger::kInfo, FUNCTION, FILENAME, line);
      logger.log(message, ILogger::kInfo, FUNCTION, FILENAME, line + 1);
      logger.log(message, ILogger::kInfo, FUNCTION, FILENAME, line + 2);
      logger.flush();

      std::string expected = getLogString(ILogger::kInfo, message, line, FUNCTION, FILENAME);
      expected.push_back('\n');
      expected.append(getLogString(ILogger::kInfo, message, line + 1, FUNCTION, FILENAME));
      expected.push_back('\n');
      expected.append(getLogString(ILogger::kInfo, message, line + 2, FUNCTION, FILENAME));

      Assert::AreEqual(expected + "\n", logger.getLog());

      checkLogFile(expected);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Logger_FlushingDuringWriting_WritesBackBuffer_AndSwapsBuffers)
    {
      std::string message;
      for (size_t i = 0; i < (size_t)(LOGGER_BUFFER_SIZE * 0.35f); ++i)
      {
        message.append("S");
      }

      Celeste::Logger logger(logFilePath);
      int line = LINE;

      logger.log(message, ILogger::kInfo, FUNCTION, FILENAME, line);
      logger.log(message, ILogger::kInfo, FUNCTION, FILENAME, line + 1);

      // Logger will flush when writing this message
      logger.log(message, ILogger::kInfo, FUNCTION, FILENAME, line + 2);

      std::string expected = getLogString(ILogger::kInfo, message, line, FUNCTION, FILENAME);
      expected.push_back('\n');
      expected.append(getLogString(ILogger::kInfo, message, line + 1, FUNCTION, FILENAME));

      // The first two messages will be in the log back buffer
      Assert::AreEqual(expected + "\n", logger.getLog());

      checkLogFile(expected);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Logger_Log_ShouldFlushAfterEveryLog_WritesToFileWithEveryMessage)
    {
      // Non flushing behaviour
      {
        Celeste::Logger nonFlushingLogger(logFilePath);
        nonFlushingLogger.shouldFlushAfterEveryLog(false);

        nonFlushingLogger.log("Test", ILogger::kInfo, FUNCTION, FILENAME, LINE);
        nonFlushingLogger.log("Non Flushing", ILogger::kInfo, FUNCTION, FILENAME, LINE);
        nonFlushingLogger.log("Logger", ILogger::kInfo, FUNCTION, FILENAME, LINE);

        checkLogFile("");
      }

      // Flushing behaviour for comparison
      {
        Celeste::Logger flushingLogger(logFilePath);
        flushingLogger.shouldFlushAfterEveryLog(true);

        int line = LINE;

        flushingLogger.log("Test", ILogger::kInfo, FUNCTION, FILENAME, line);
        flushingLogger.log("Flushing", ILogger::kInfo, FUNCTION, FILENAME, line + 1);
        flushingLogger.log("Logger", ILogger::kInfo, FUNCTION, FILENAME, line + 2);

        std::string expected = getLogString(ILogger::kInfo, "Test", line, FUNCTION, FILENAME);
        expected.push_back('\n');
        expected.append(getLogString(ILogger::kInfo, "Flushing", line + 1, FUNCTION, FILENAME));
        expected.push_back('\n');
        expected.append(getLogString(ILogger::kInfo, "Logger", line + 2, FUNCTION, FILENAME));

        checkLogFile(expected);
      }
    }

#pragma endregion

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Logger_Destructor_WritesBothBuffersToFile)
    {
      int line = LINE;
      std::string function = FUNCTION;
      std::string filename = FILENAME;

      std::string expected = getLogString(ILogger::kInfo, "Test", line, function, filename);

      // Scope the logger so it is destroyed in this section of the test rather than at the end of the function
      // This is to trigger the destructor
      {
        Celeste::Logger logger(logFilePath);
        logger.log("Test", ILogger::kInfo, FUNCTION, FILENAME, line);
      }

      checkLogFile(expected);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Logger_Clear_ClearsBothBuffersAndLogFile)
    {
      Celeste::Logger logger(logFilePath);
      logger.log("Just logging something", ILogger::kInfo, FUNCTION, FILENAME, LINE);
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