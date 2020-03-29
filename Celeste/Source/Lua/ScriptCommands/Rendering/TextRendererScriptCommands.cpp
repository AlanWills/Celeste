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
      "setText", &Celeste::Rendering::TextRenderer::setText);
  }
}