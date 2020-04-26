#include "ScriptCommands/Rendering/SpriteRendererScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Rendering/SpriteRenderer.h"
#include "sol/sol.hpp"

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
    void setDimensions_TwoFloatsOverload(SpriteRenderer& spriteRenderer, float width, float height)
    {
      spriteRenderer.setDimensions(width, height);
    }

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
  void initialize(sol::state& state)
  {
    registerUserType<SpriteRenderer>(
      state,
      SpriteRenderer::type_name(),
      sol::base_classes, sol::bases<Component, Entity, Object>(),
      "getDimensions", &SpriteRenderer::getDimensions,
      "setDimensions", &Internals::setDimensions_TwoFloatsOverload,
      "setTexture", sol::overload(&Internals::setTexture_HandleOverload, &Internals::setTexture_StringOverload),
      "setColour", &Internals::setColour_ThreeFloatsOverload);
  }
}