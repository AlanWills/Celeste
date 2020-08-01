#include "CrashHandler/LogStackWalker.h"
#include "Log/Log.h"


namespace CrashHandler
{
  //------------------------------------------------------------------------------------------------
  void LogStackWalker::OnOutput(LPCSTR szText)
  {
    Celeste::Log::critical(szText);
    Celeste::Log::flush();
  }
}