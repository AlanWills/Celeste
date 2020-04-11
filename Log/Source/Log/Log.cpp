#include "Log/Log.h"
#include "Log/StdoutLogger.h"
#include "FileSystem/Directory.h"


namespace Celeste::Log
{
  std::unique_ptr<ILogger> Logging::m_logger = std::unique_ptr<ILogger>(new StdoutLogger());

  //------------------------------------------------------------------------------------------------
  Logging::Logging()
  {
  }

  //------------------------------------------------------------------------------------------------
  Logging& Logging::instance()
  {
    static Logging instance;
    return instance;
  }

  //------------------------------------------------------------------------------------------------
  void Logging::setLogger(std::unique_ptr<ILogger>&& logger)
  { 
    m_logger = std::move(logger); 
  }

  //------------------------------------------------------------------------------------------------
  ILogger& Logging::getLogger()
  { 
    return *m_logger; 
  }
}