#include "Debug/Logging/FileLogger.h"
#include "FileSystem/Directory.h"

#include <thread>


namespace Celeste::Log
{
  //------------------------------------------------------------------------------------------------
  FileLogger::FileLogger(const std::string& logFileFullPath) :
    m_shouldFlushAfterEveryLog(false),
    m_logFile(logFileFullPath),
    m_verbosity(Verbosity::kRaw | Verbosity::kInfo | Verbosity::kWarning | Verbosity::kError | Verbosity::kCriticalError)
  {
    m_backLogBufferStr.reserve(LOGGER_BUFFER_SIZE);
    m_backLogBufferStr.clear();

    // Clears the log file if it already exists or creates it if not
    m_logFile.create();
  }

  //------------------------------------------------------------------------------------------------
  FileLogger::~FileLogger()
  {
    // When this is destroyed, we write the contents of the front buffer to the log file
    // Anything in the back buffer will have already been written
    flush();
  }

  //------------------------------------------------------------------------------------------------
  /*void asyncWriteToLogFile(const std::string& logFileFullPath, const std::string& bufferedLog)
  {
    File::appendToFile(logFileFullPath, bufferedLog);
  }*/

  //------------------------------------------------------------------------------------------------
  void FileLogger::log(
    const std::string& message,
    Verbosity verbosity,
    const char* function,
    const char* file,
    int line)
  {
    // If we have not indicated that the logger should log messages of the inputted verbosity
    // Then we do not log the message
    if ((m_verbosity & static_cast<int>(verbosity)) == 0)
    {
      return;
    }

    std::string fullMessage(message);

    // Don't decorate raw logs
    if ((Verbosity::kRaw & static_cast<int>(verbosity)) == 0)
    {
      fullMessage.clear();
      fullMessage.reserve(1024);

      fullMessage.append(getVerbosityString(verbosity));
      fullMessage.append(": ");
      fullMessage.append(message);
      fullMessage.append(" in function: ");
      fullMessage.append(function);
      fullMessage.append(", in file: ");
      fullMessage.append(file);
      fullMessage.append(", on line: ");
      fullMessage.append(std::to_string(line));
    }

    // Store the message into our buffer and add a new line to the end of it
    AllocateResult allocResult = m_logBuffer.copy(fullMessage.length() + 1, (fullMessage + "\n").c_str());

    if (m_shouldFlushAfterEveryLog && allocResult != AllocateResult::kSwapRequired)
    {
      // We didn't require a swap but we will be flushing the log so we manually swap the buffers here
      m_logBuffer.swapBuffers();
    }

    if (m_shouldFlushAfterEveryLog || allocResult == AllocateResult::kSwapRequired)
    {
      writeLogBackBufferToFile();
    }
  }

  //------------------------------------------------------------------------------------------------
  void FileLogger::flush()
  {
    m_logBuffer.swapBuffers();

    writeLogBackBufferToFile();
  }

  //------------------------------------------------------------------------------------------------
  void FileLogger::writeLogBackBufferToFile()
  {
    m_logFile.append(getLog());
  }

  //------------------------------------------------------------------------------------------------
  const std::string& FileLogger::getLog()
  {
    m_backLogBufferStr.clear();

    const char* bufferedMessages = nullptr;
    size_t bufferedDataCount = m_logBuffer.getBufferedData(&bufferedMessages);

    m_backLogBufferStr.append(bufferedMessages, bufferedDataCount);

    return m_backLogBufferStr;
  }

  //------------------------------------------------------------------------------------------------
  void FileLogger::clear()
  {
    m_logBuffer.deallocateAll();
    m_logFile.clear();
  }

  //------------------------------------------------------------------------------------------------
  const char* FileLogger::getVerbosityString(Verbosity verbosity)
  {
    switch (verbosity)
      {
      case Verbosity::kRaw:
        return "";

      case Verbosity::kInfo:
        return INFO_STRING;

      case Verbosity::kWarning:
        return WARNING_STRING;

      case Verbosity::kError:
        return ERROR_STRING;

      case Verbosity::kCriticalError:
        return CRITICAL_ERROR_STRING;

      default:
        ASSERT_FAIL();
        return "";
    }
  }
}