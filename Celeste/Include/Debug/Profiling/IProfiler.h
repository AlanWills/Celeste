#pragma once

#include "CelesteDllExport.h"
#include <string>


namespace Celeste
{
  class ProfilingBlock;

  class CelesteDllExport IProfiler
  {
    public:
      virtual ~IProfiler() {}

      virtual void beginProfilingBlock(const std::string& profilingBlockName) = 0;
      virtual void endProfilingBlock(const std::string& profilingBlockName) = 0;
      virtual const ProfilingBlock* getProfilingBlock(const std::string& profilingBlockName) = 0;
  };
}