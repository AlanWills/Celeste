#include "Lua/ScriptCommands/Rendering/CanvasScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"
#include "Rendering/Canvas.h"

#include "Deserialization/ViewportDeserializers.h"

using ProjectionMode = Celeste::ProjectionMode;


namespace Celeste::Lua::Rendering::CanvasScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    using Canvas = Celeste::Rendering::Canvas;

    registerUserType<Canvas>(
      "Canvas",
      sol::base_classes, sol::bases<Component, Entity, Object>());
  }
}