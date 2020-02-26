#include "Maths/Matrix.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  glm::mat4 createMatrix(
    const glm::vec3& translation,
    float rotation,
    const glm::vec3& scale)
  {
    glm::mat4 localMatrix;
    localMatrix[3].x = translation.x;
    localMatrix[3].y = translation.y;
    localMatrix[3].z = translation.z;
    localMatrix = glm::rotate(localMatrix, -rotation, glm::vec3(0, 0, 1));
    
    return glm::scale(localMatrix, scale);
  }

  //------------------------------------------------------------------------------------------------
  glm::mat4 createInverseMatrix(
    const glm::vec3& translation,
    float rotation,
    const glm::vec3& scale)
  {
    glm::mat4 inverseMatrix;
    inverseMatrix = glm::scale(inverseMatrix, scale);
    inverseMatrix = glm::rotate(inverseMatrix, -rotation, glm::vec3(0, 0, 1));

    // scale and rotate do not affect translation, but we need the translation to be scaled too
    inverseMatrix[3] = inverseMatrix * glm::vec4(translation, 1);

    return inverseMatrix;
  }
}