#include "ScriptCommands/Rendering/TextRendererScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Rendering/TextRenderer.h"
#include "sol/sol.hpp"


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Rendering::TextRenderer> : std::false_type {};
}

namespace Celeste::Lua::Rendering::TextRendererScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    registerUserType<Celeste::Rendering::TextRenderer>(
      state,
      Celeste::Rendering::TextRenderer::type_name(),
      sol::base_classes, sol::bases<Component, Entity, Object>(),
      "setText", &Celeste::Rendering::TextRenderer::setText);
  }
}