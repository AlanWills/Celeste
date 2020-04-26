#include "ScriptCommands/Rendering/RenderingScriptCommands.h"
#include "ScriptCommands/Rendering/CanvasScriptCommands.h"
#include "ScriptCommands/Rendering/TextRendererScriptCommands.h"
#include "ScriptCommands/Rendering/SpriteRendererScriptCommands.h"
#include "sol/sol.hpp"


namespace Celeste::Lua::Rendering::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    CanvasScriptCommands::initialize(state);
    TextRendererScriptCommands::initialize(state);
    SpriteRendererScriptCommands::initialize(state);
  }
}