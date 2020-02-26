#include "Lua/ScriptCommands/Rendering/TextRendererScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"
#include "Rendering/TextRenderer.h"


namespace Celeste::Lua::Rendering::TextRendererScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<Celeste::Rendering::TextRenderer>(
      "TextRenderer",
      "allocate", sol::factories(&Celeste::Rendering::TextRenderer::allocate),
      "setText", &Celeste::Rendering::TextRenderer::setText);
  }
}