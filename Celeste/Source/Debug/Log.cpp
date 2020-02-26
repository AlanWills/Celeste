#include "Debug/Log.h"
#include "Debug/Logging/Logger.h"
#include "FileSystem/Directory.h"


namespace Celeste
{
  std::unique_ptr<ILogger> Log::m_logger = std::unique_ptr<ILogger>(new Logger(Path(Directory::getExecutingAppDirectory(), "Log.txt")));

  //------------------------------------------------------------------------------------------------
  Log::Log()
  {
  }

  //------------------------------------------------------------------------------------------------
  Log& Log::instance()
  {
    static Log instance;
    return instance;
  }

  //------------------------------------------------------------------------------------------------
  void Log::setLogger(ILogger* asserter) 
  { 
    m_logger.reset(asserter); 
  }

  //------------------------------------------------------------------------------------------------
  ILogger* Log::getLogger()
  { 
    return m_logger.get(); 
  }
}