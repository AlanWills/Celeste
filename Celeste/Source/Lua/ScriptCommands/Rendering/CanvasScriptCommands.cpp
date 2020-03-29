#include "Lua/ScriptCommands/Rendering/CanvasScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"
#include "Rendering/Canvas.h"

#include "Deserialization/ViewportDeserializers.h"

using ProjectionMode = Celeste::ProjectionMode;


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Rendering::Canvas> : std::false_type {};
}

namespace Celeste::Lua::Rendering::CanvasScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    using Canvas = Celeste::Rendering::Canvas;

    registerUserType<Canvas>(
      Canvas::type_name(),
      sol::base_classes, sol::bases<Component, Entity, Object>());
  }
}