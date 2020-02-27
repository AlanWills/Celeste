#pragma once

#include "Renderer.h"
#include "FileSystem/Path.h"

#include <string>


namespace Celeste::Resources
{
  class Texture2D;
}

namespace Celeste::Rendering
{
  enum class RatioMode
  {
    kPreserveAspectRatio = true,
    kDontPreserveAspectRatio = false
  };

  // A class which is responsible for rendering a texture using the sprite shader
  class SpriteRenderer : public Renderer
  {
    DECLARE_SCRIPT(SpriteRenderer, CelesteDllExport)

    public:
      CelesteDllExport void render(const Resources::Program& shaderProgram, const glm::mat4& viewModelMatrix) const override;

      /// Load a texture from the resource manager and set it as the texture to render on this sprite renderer
      CelesteDllExport void setTexture(const Path& textureRelativeString);

      /// Sets the current rendered texture to be the inputted value
      CelesteDllExport void setTexture(Resources::Texture2D* texture);

      inline Resources::Texture2D* getTexture() const { return m_texture; }

      /// Set the dimensions of the texture being rendered
      CelesteDllExport void setDimensions(const glm::vec2& dimensions);
      void setDimensions(float x, float y) { setDimensions(glm::vec2(x, y)); }

      /// Returns the dimensions of the texture being rendered
      inline glm::vec2 getDimensions() const override { return m_dimensions; }

      inline bool isPreservingAspectRatio() const { return m_preserveAspectRatio; }
      inline void shouldPreserveAspectRatio(Rendering::RatioMode shouldPreserveAspectRatio) { m_preserveAspectRatio = shouldPreserveAspectRatio == Rendering::RatioMode::kPreserveAspectRatio; }

    private:
      using Inherited = Renderer;

      Resources::Texture2D* m_texture;
      glm::vec2 m_dimensions;
      bool m_preserveAspectRatio;
  };
}