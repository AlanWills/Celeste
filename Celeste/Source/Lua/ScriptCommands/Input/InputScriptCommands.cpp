#include "Lua/ScriptCommands/Input/InputScriptCommands.h"
#include "Lua/ScriptCommands/Input/KeyboardActivatorScriptCommands.h"
#include "Lua/ScriptCommands/Input/KeyboardVisibilityScriptCommands.h"
#include "Lua/ScriptCommands/Input/MouseInteractionHandlerScriptCommands.h"
#include "Lua/LuaState.h"


namespace Celeste::Lua::Input::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    KeyboardActivatorScriptCommands::initialize();
    KeyboardVisibilityScriptCommands::initialize();
    MouseInteractionHandlerScriptCommands::initialize();
  }
}