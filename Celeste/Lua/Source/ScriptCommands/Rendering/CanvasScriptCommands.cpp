#include "ScriptCommands/Rendering/CanvasScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Rendering/Canvas.h"
#include "sol/sol.hpp"

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
  void initialize(sol::state& state)
  {
    using Canvas = Celeste::Rendering::Canvas;

    registerUserType<Canvas>(
      state,
      Canvas::type_name(),
      sol::base_classes, sol::bases<Component, Entity, Object>());
  }
}