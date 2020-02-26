#pragma once

#include "glm/glm.hpp"


namespace Celeste::Maths
{
  class Ellipse
  {
    public:
      Ellipse() : Ellipse(glm::vec2(), glm::vec2()) { }
      Ellipse(const glm::vec2& centre, const glm::vec2& dimensions) : m_centre(centre), m_dimensions(dimensions) { }

      glm::vec2 m_centre;
      glm::vec2 m_dimensions;
  };
}