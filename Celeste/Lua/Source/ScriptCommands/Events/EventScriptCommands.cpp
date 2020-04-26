#include "ScriptCommands/Events/EventScriptCommands.h"
#include "ScriptCommands/Events/EventTriggererScriptCommands.h"
#include "sol/sol.hpp"


namespace Celeste::Lua::Events::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    EventTriggererScriptCommands::initialize(state);
  }
}