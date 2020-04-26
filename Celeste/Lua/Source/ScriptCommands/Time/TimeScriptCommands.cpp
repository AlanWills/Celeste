#include "ScriptCommands/Time/TimeScriptCommands.h"
#include "Time/TimeUtils.h"
#include "Time/Clock.h"
#include "sol/sol.hpp"


namespace Celeste::Lua::Time::ScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    float getDeltaTime()
    {
      return getClock().getElapsedDeltaTime();
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    sol::table timeTable = state.create_named_table("Time");
    timeTable["getDeltaTime"] = &Internals::getDeltaTime;
  }
}