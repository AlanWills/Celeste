#include "Debug/Profile.h"
#include "Debug/Profiling/Profiler.h"
#include "FileSystem/Directory.h"


namespace Celeste
{
  std::unique_ptr<IProfiler> Profile::m_profiler = std::unique_ptr<IProfiler>(new Profiler(Path(Directory::getExecutingAppDirectory(), "Profiler.txt")));

  //------------------------------------------------------------------------------------------------
  Profile::Profile()
  {
  }

  //------------------------------------------------------------------------------------------------
  Profile& Profile::instance()
  {
    static Profile instance;
    return instance;
  }

  //------------------------------------------------------------------------------------------------
  void Profile::setProfiler(IProfiler* profiler) 
  { 
    m_profiler.reset(profiler); 
  }

  //------------------------------------------------------------------------------------------------
  IProfiler* Profile::getProfiler() 
  { 
    return m_profiler.get(); 
  }
}