#include "Lua/ScriptCommands/UI/UIScriptCommands.h"
#include "Lua/ScriptCommands/UI/StackPanelScriptCommands.h"
#include "Lua/ScriptCommands/UI/ProgressBarScriptCommands.h"
#include "Lua/ScriptCommands/UI/SliderScriptCommands.h"


namespace Celeste::Lua::UI::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    StackPanelScriptCommands::initialize();
    ProgressBarScriptCommands::initialize();
    SliderScriptCommands::initialize();
  }
}