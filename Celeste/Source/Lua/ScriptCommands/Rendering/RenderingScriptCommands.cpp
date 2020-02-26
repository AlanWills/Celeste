#include "Lua/ScriptCommands/Rendering/RenderingScriptCommands.h"
#include "Lua/ScriptCommands/Rendering/CanvasScriptCommands.h"
#include "Lua/ScriptCommands/Rendering/TextRendererScriptCommands.h"
#include "Lua/ScriptCommands/Rendering/SpriteRendererScriptCommands.h"
#include "Lua/LuaState.h"


namespace Celeste::Lua::Rendering::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    CanvasScriptCommands::initialize();
    TextRendererScriptCommands::initialize();
    SpriteRendererScriptCommands::initialize();
  }
}