#pragma once

#include <functional>
#include <signal.h>
#include <stdexcept>


namespace CrashHandler
{
  using SegmentationFaultHandler = _crt_signal_t;
  using UncaughtExceptionHandler = terminate_handler;

  void setDefaultSegmentationFaultHandler();
  void setDefaultUncaughtExceptionHandler();

  void setSegmentationFaultHandler(SegmentationFaultHandler handler);
  void setUncaughtExceptionHandler(UncaughtExceptionHandler handler);
}