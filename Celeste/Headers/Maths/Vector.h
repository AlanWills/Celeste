#pragma once

#include "CelesteDllExport.h"
#include "glm/glm.hpp"


namespace Celeste
{
  namespace Maths
  {
    inline float CelesteDllExport length_squared(const glm::vec3& v1)
    {
      return v1.x * v1.x + v1.y * v1.y + v1.z * v1.z;
    }
  }
}