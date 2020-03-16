#pragma once

#include "CelesteDllExport.h"

#include <string>
#include <functional>


namespace Celeste
{
  namespace System
  {
    class CelesteDllExport Process
    {
      public:
        using OnProcessCompleteCallback = std::function<void()>;

        static void start(const std::string& commandLine, const OnProcessCompleteCallback& onProcessComplete = nullptr);

      private:
        Process() = default;
    };
  }
}