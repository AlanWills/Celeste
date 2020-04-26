#include "ScriptCommands/UI/UIScriptCommands.h"
#include "ScriptCommands/UI/StackPanelScriptCommands.h"
#include "ScriptCommands/UI/ProgressBarScriptCommands.h"
#include "ScriptCommands/UI/SliderScriptCommands.h"
#include "sol/sol.hpp"


namespace Celeste::Lua::UI::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    StackPanelScriptCommands::initialize(state);
    ProgressBarScriptCommands::initialize(state);
    SliderScriptCommands::initialize(state);
  }
}