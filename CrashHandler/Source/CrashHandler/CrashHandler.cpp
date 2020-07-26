#include "CrashHandler/CrashHandler.h"
#include "CrashHandler/LogStackWalker.h"
#include "Log/Log.h"

#include <cstdlib>
#include <cstdio>
#include <exception>


namespace CrashHandler
{
  //------------------------------------------------------------------------------------------------
  void defaultSegmentationFaultHandler(int seg)
  {
    LOG_CRITICAL_ERROR("Error Signal: " + std::to_string(seg));
    LogStackWalker().ShowCallstack();
    std::abort();
  }

  //------------------------------------------------------------------------------------------------
  void defaultUncaughtExceptionHandler()
  {
    std::exception_ptr exptr = std::current_exception();
    if (exptr != 0)
    {
      // the only useful feature of std::exception_ptr is that it can be rethrown...
      try
      {
        std::rethrow_exception(exptr);
      }
      catch (std::exception& ex)
      {
        std::fprintf(stderr, "Terminated due to exception: %s\n", ex.what());
      }
      catch (...)
      {
        std::fprintf(stderr, "Terminated due to unknown exception\n");
      }
    }
    else
    {
      std::fprintf(stderr, "Terminated due to unknown reason :(\n");
    }

    LogStackWalker().ShowCallstack();
    std::abort();
  }

  //------------------------------------------------------------------------------------------------
  void setDefaultSegmentationFaultHandler()
  {
    setSegmentationFaultHandler(defaultSegmentationFaultHandler);
  }

  //------------------------------------------------------------------------------------------------
  void setDefaultUncaughtExceptionHandler()
  {
    setUncaughtExceptionHandler(defaultUncaughtExceptionHandler);
  }

  //------------------------------------------------------------------------------------------------
  void setSegmentationFaultHandler(SegmentationFaultHandler handler)
  {
    signal(SIGSEGV, handler);
  }

  //------------------------------------------------------------------------------------------------
  void setUncaughtExceptionHandler(UncaughtExceptionHandler handler)
  {
    std::set_terminate(handler);
  }
}