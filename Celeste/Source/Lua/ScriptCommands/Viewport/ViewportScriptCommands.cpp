#include "Lua/ScriptCommands/Viewport/ViewportScriptCommands.h"
#include "Lua/LuaState.h"

#include "Scene/SceneUtils.h"


namespace Celeste::Lua::Viewport::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    sol::table viewportTable = Lua::LuaState::instance().create_named_table("Viewport");
    viewportTable["getDimensions"] = &getViewportDimensions;
  }
}