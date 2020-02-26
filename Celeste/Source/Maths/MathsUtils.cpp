#include "Maths/MathsUtils.h"


namespace Celeste
{
  namespace Maths
  {
    //------------------------------------------------------------------------------------------------
    float lookAt(const glm::vec3& currentPosition, const glm::vec2& targetPosition)
    {
      return std::atan2f(targetPosition.x - currentPosition.x, targetPosition.y - currentPosition.y);
    }

    //------------------------------------------------------------------------------------------------
    float lookAt(const glm::vec3& currentPosition, const glm::vec3& targetPosition)
    {
      return lookAt(currentPosition, glm::vec2(targetPosition.x, targetPosition.y));
    }
  }
}