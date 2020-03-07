#include "Lua/ScriptCommands/Events/EventScriptCommands.h"
#include "Lua/ScriptCommands/Events/EventTriggererScriptCommands.h"
#include "Lua/LuaState.h"


namespace Celeste::Lua::Events::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    EventTriggererScriptCommands::initialize();
  }
}