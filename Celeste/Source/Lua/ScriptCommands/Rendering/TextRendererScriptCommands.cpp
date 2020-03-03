#include "Lua/ScriptCommands/Rendering/TextRendererScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"
#include "Rendering/TextRenderer.h"


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