#pragma once

#include "glm/glm.hpp"


namespace Celeste::Maths
{
  class Ray
  {
    public:
      Ray() : m_origin(glm::vec3()), m_direction(glm::vec3(0, 0, -1)) { }
      Ray(const glm::vec3& origin, const glm::vec3& direction) : m_origin(origin), m_direction(direction) { }

      glm::vec3 m_origin;
      glm::vec3 m_direction;
  };
}