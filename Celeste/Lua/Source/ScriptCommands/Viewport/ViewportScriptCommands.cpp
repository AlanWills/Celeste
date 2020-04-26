#include "ScriptCommands/Viewport/ViewportScriptCommands.h"
#include "Scene/SceneUtils.h"
#include "sol/sol.hpp"


namespace Celeste::Lua::Viewport::ScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    sol::table viewportTable = state.create_named_table("Viewport");
    viewportTable["getDimensions"] = &getViewportDimensions;
  }
}