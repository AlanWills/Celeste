#pragma once

#include "CelesteDllExport.h"
#include "UtilityHeaders/GLHeaders.h"


namespace Celeste
{
  CelesteDllExport glm::mat4 createMatrix(
    const glm::vec3& translation, 
    float rotation, 
    const glm::vec3& scale);

  CelesteDllExport glm::mat4 createInverseMatrix(
    const glm::vec3& inverseTranslation,
    float inverseRotation,
    const glm::vec3& inverseScale);
}