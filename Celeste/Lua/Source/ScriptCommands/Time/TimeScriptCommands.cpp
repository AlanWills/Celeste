#include "ScriptCommands/Time/TimeScriptCommands.h"
#include "ScriptCommands/Time/TimeNotifierSystemScriptCommands.h"
#include "Time/TimeUtils.h"
#include "sol/sol.hpp"


namespace Celeste::Lua::Time::ScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    float getDeltaTime()
    {
      return Celeste::Time::getElapsedDeltaTime();
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    sol::table timeTable = state.create_named_table("Time");
    timeTable["getDeltaTime"] = &Internals::getDeltaTime;

    TimeNotifierSystemScriptCommands::initialize(state);
  }
}