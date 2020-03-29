#include "Lua/ScriptCommands/Rendering/SpriteRendererScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"
#include "Rendering/SpriteRenderer.h"

using SpriteRenderer = Celeste::Rendering::SpriteRenderer;


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Rendering::SpriteRenderer> : std::false_type {};
}

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
      SpriteRenderer::type_name(),
      sol::base_classes, sol::bases<Component, Entity, Object>(),
      "setTexture", sol::overload(&Internals::setTexture_HandleOverload, &Internals::setTexture_StringOverload),
      "setColour", &Internals::setColour_ThreeFloatsOverload);
  }
}