#pragma once

#include "Memory/Allocators/DoubleBufferAllocator.h"
#include "FileSystem/File.h"
#include "ILogger.h"


namespace Celeste
{
  #define INFO_STRING "Info"
  #define WARNING_STRING "Warning"
  #define ERROR_STRING "Error"
  #define CRITICAL_ERROR_STRING "Critical Error"

  #define LOGGER_BUFFER_SIZE 2048

  // A class used to log information
  // Also writes to a file when it's buffer becomes too large
  // Any messages in the front buffer of the log are considered 'untouchable'
  // If you wish to obtain them, call flush() and then call getLog() or read from the log file
  class Logger : public ILogger
  {
    public:
      /// \brief Pass in a custom path relative to the executing directory to specify the output log file
      CelesteDllExport Logger(const std::string& logFileFullPath);
      CelesteDllExport Logger(const Path& logFilePath) : Logger(logFilePath.as_string()) { }
      CelesteDllExport ~Logger() override;

      /// \brief Custom logging function which also records the error warning level
      /// If the log is set to ignore errors of the inputted verbosity, this error will instead be dismissed
      /// Use the FUNCTION, FILENAME and LINE macros for the last three parameters
      CelesteDllExport void log(const std::string& message, Verbosity verbosity, const char* function, const char* file, int line) override;

      /// \brief Returns the string in the back log buffer
      CelesteDllExport const std::string& getLog() override;

      /// \brief Swaps the front log buffer with the back log buffer and writes the new back log buffer contents to the file
      /// Call when you have logged messages and you wish to write them to file and then discard them
      CelesteDllExport void flush() override;

      /// \brief By default the logger buffers messages into batches before logging
      /// However, if we wish to log every message immediately then set this to true
      /// Be wary of using this in performance sensitive code
      void shouldFlushAfterEveryLog(bool shouldFlushAfterEveryLog) { m_shouldFlushAfterEveryLog = shouldFlushAfterEveryLog; }

      /// Clears the back and front buffers of the logger and the log file
      CelesteDllExport void clear() override;

    private:
      /// \brief Obtain a string we will use to build our error logging based on the inputted verbosity
      static const char* getVerbosityString(Verbosity verbosity);
      
      void writeLogBackBufferToFile();

      // The memory we will write to and use to write to the log file
      DoubleBufferAllocator<char, LOGGER_BUFFER_SIZE> m_logBuffer;

      File m_logFile;
      std::string m_backLogBufferStr;
      bool m_shouldFlushAfterEveryLog;
      int m_verbosity;
  };
}