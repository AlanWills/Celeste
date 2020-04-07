#pragma once

#include "glm/glm.hpp"


namespace Celeste::Maths
{
  inline float length_squared(const glm::vec3& v1)
  {
    return v1.x * v1.x + v1.y * v1.y + v1.z * v1.z;
  }
}