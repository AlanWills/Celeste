#pragma once


namespace Celeste::Log
{
  enum Verbosity : int
  {
    kRaw = 1 << 0, // Straight up text that will not be decorated
    kInfo = 1 << 1, // General information
    kWarning = 1 << 2,  // Warnings are failures that should be fixed but the game can still run
    kError = 1 << 3,    // Errors constitute more serious problems that should be fixed immediately - the game may or may not be able to continue running
    kCriticalError = 1 << 4,  // Critical errors correspond to crashes
  };
}