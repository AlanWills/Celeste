#include "Lua/ScriptCommands/Rendering/TextRendererScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"
#include "Rendering/TextRenderer.h"


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Rendering::TextRenderer> : std::false_type {};
}

namespace Celeste::Lua::Rendering::TextRendererScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<Celeste::Rendering::TextRenderer>(
      Celeste::Rendering::TextRenderer::type_name(),
      sol::base_classes, sol::bases<Component, Entity, Object>(),
      "setText", &Celeste::Rendering::TextRenderer::setText);
  }
}