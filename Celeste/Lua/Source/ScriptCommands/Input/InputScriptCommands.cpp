#include "ScriptCommands/Input/InputScriptCommands.h"
#include "ScriptCommands/Input/MouseScriptCommands.h"
#include "ScriptCommands/Input/KeyScriptCommands.h"
#include "ScriptCommands/Input/KeyboardScriptCommands.h"
#include "ScriptCommands/Input/KeyboardActivatorScriptCommands.h"
#include "ScriptCommands/Input/KeyboardVisibilityScriptCommands.h"
#include "ScriptCommands/Input/MouseInteractionHandlerScriptCommands.h"
#include "sol/sol.hpp"


namespace Celeste::Lua::Input::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    MouseScriptCommands::initialize(state);
    KeyboardScriptCommands::initialize(state);
    KeyScriptCommands::initialize(state);
    KeyboardActivatorScriptCommands::initialize(state);
    KeyboardVisibilityScriptCommands::initialize(state);
    MouseInteractionHandlerScriptCommands::initialize(state);
  }
}