#pragma once

#include "CelesteDllExport.h"
#include "glm/glm.hpp"


namespace Celeste
{
  namespace Maths
  {
    float CelesteDllExport lookAt(const glm::vec3& currentPosition, const glm::vec2& targetPosition);
    float CelesteDllExport lookAt(const glm::vec3& currentPosition, const glm::vec3& targetPosition);
  }
}