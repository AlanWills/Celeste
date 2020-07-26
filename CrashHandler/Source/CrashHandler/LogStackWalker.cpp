#include "CrashHandler/LogStackWalker.h"
#include "Log/Log.h"


namespace CrashHandler
{
  //------------------------------------------------------------------------------------------------
  void LogStackWalker::OnOutput(LPCSTR szText)
  {
    LOG_CRITICAL_ERROR(szText);
    Celeste::Log::Logging::getLogger().flush();
  }
}