#pragma once

#include "Objects/Component.h"
#include "Maths/Rectangle.h"


namespace Celeste::Resources
{
  class Program;
}

namespace Celeste::Rendering
{
  class Renderer : public Component
  {
    public:
      CelesteDllExport Renderer(GameObject& gameObject);

      static constexpr bool isManaged() { return false; }

      virtual void render(const Resources::Program& shaderProgram, const glm::mat4& viewModelMatrix) const = 0;

      inline const glm::vec2& getOrigin() const { return m_origin; }
      inline void setOrigin(const glm::vec2& origin) { m_origin = origin; }
      inline void setOrigin(float x, float y) { setOrigin(glm::vec2(x, y)); }

      inline const glm::vec4& getColour() const { return m_colour; }
      inline void setColour(const glm::vec3& colour) { setColour(colour.x, colour.y, colour.z); }
      inline void setColour(const glm::vec4& colour) { m_colour = colour; }
      inline void setColour(float r, float g, float b) { setColour(glm::vec4(r, g, b, m_colour.a)); }
      inline void setColour(float r, float g, float b, float a) { setColour(glm::vec4(r, g, b, a)); }

      inline float getOpacity() const { return m_colour.a; }
      inline void setOpacity(float opacity) { m_colour.a = opacity; }

      inline Maths::Rectangle& getScissorRectangle() { return m_scissorRectangle; }
      inline const Maths::Rectangle& getScissorRectangle() const { return m_scissorRectangle; }

      /// Returns the raw size of the item being rendered
      virtual glm::vec2 getDimensions() const = 0;

      /// Returns the raw size of the item being rendered multiplied by the game objects local scale
      CelesteDllExport glm::vec2 getScaledDimensions() const;

    private:
      using Inherited = Component;

      glm::vec2 m_origin;
      glm::vec4 m_colour;
      Maths::Rectangle m_scissorRectangle;
  };
}