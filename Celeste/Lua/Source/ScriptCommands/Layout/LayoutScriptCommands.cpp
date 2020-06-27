#include "ScriptCommands/Layout/LayoutScriptCommands.h"
#include "ScriptCommands/Layout/LayoutSystemScriptCommands.h"
#include "ScriptCommands/Layout/ResolutionScalerScriptCommands.h"
#include "sol/sol.hpp"


namespace Celeste::Lua::Layout::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    LayoutSystemScriptCommands::initialize(state);
    ResolutionScalerScriptCommands::initialize(state);
  }
}