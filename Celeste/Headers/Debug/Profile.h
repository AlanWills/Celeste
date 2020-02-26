#pragma once

#include "Profiling/IProfiler.h"

#include <memory>

#ifdef _DEBUG
#define BEGIN_PROFILING_BLOCK(name) Celeste::Profile::getProfiler()->beginProfilingBlock(name);
#else
#define BEGIN_PROFILING(name)
#endif

#ifdef _DEBUG
#define END_PROFILING_BLOCK(name) Celeste::Profile::getProfiler()->endProfilingBlock(name);
#else
#define END_PROFILING_BLOCK(name)
#endif

namespace Celeste
{
  class Profile
  {
    public:
      Profile(const Profile&) = delete;
      Profile(Profile&&) = delete;
      void operator=(const Profile&) = delete;

      CelesteDllExport static void setProfiler(IProfiler* profiler);
      CelesteDllExport static IProfiler* getProfiler();

    private:
      Profile();
      static Profile& instance();

      static std::unique_ptr<IProfiler> m_profiler;
  };
}