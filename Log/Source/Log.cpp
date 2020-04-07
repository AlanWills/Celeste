#include "Log.h"
#include "Logging/StdoutLogger.h"
#include "FileSystem/Directory.h"


namespace Celeste
{
  std::unique_ptr<ILogger> Log::m_logger = std::unique_ptr<ILogger>(new StdoutLogger());

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
  void Log::setLogger(std::unique_ptr<ILogger>&& logger) 
  { 
    m_logger = std::move(logger); 
  }

  //------------------------------------------------------------------------------------------------
  ILogger& Log::getLogger()
  { 
    return *m_logger; 
  }
}