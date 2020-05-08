#include "ScriptCommands/System/SystemScriptCommands.h"
#include "sol/sol.hpp"


namespace Celeste::Lua::System::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    if (!state["System"].valid())
    {
      state.create_named_table("System");
    }
  }
}