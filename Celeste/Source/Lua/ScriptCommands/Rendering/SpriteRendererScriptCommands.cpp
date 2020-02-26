#include "Lua/ScriptCommands/Rendering/SpriteRendererScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"
#include "Rendering/SpriteRenderer.h"

using SpriteRenderer = Celeste::Rendering::SpriteRenderer;


namespace Celeste::Lua::Rendering::SpriteRendererScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void setTexture_HandleOverload(SpriteRenderer& spriteRenderer, observer_ptr<Celeste::Resources::Texture2D> texture)
    {
      spriteRenderer.setTexture(texture);
    }

    //------------------------------------------------------------------------------------------------
    void setTexture_StringOverload(SpriteRenderer& spriteRenderer, const std::string& texturePath)
    {
      spriteRenderer.setTexture(texturePath);
    }

    //------------------------------------------------------------------------------------------------
    void setColour_ThreeFloatsOverload(SpriteRenderer& spriteRenderer, float r, float g, float b)
    {
      spriteRenderer.setColour(r, g, b);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<SpriteRenderer>(
      "SpriteRenderer",
      "allocate", sol::factories(&SpriteRenderer::allocate),
      "setTexture", sol::overload(&Internals::setTexture_HandleOverload, &Internals::setTexture_StringOverload),
      "setColour", &Internals::setColour_ThreeFloatsOverload);
  }
}