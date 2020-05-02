#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Maths/Matrix.h"
#include "TestUtils/Assert/AssertExt.h"


namespace TestCeleste
{

  CELESTE_TEST_CLASS(TestMatrix)

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_CreateMatrix)
    {
      glm::mat4 expected = glm::identity<glm::mat4>();
      expected[3] = glm::vec4(2, -1, 1, 1);
      expected = glm::rotate(expected, -glm::half_pi<float>(), glm::vec3(0, 0, 1));
      expected = glm::scale(expected, glm::vec3(0.5f, 0.25f, 1));

      AssertExt::AreAlmostEqual(expected, Celeste::createMatrix(glm::vec3(2, -1, 1), glm::half_pi<float>(), glm::vec3(0.5f, 0.25f, 1)));
    }


    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_CreateInverseMatrix)
    {
      glm::mat4 expected = glm::identity<glm::mat4>();
      expected[3] = glm::vec4(2, -1, 1, 1);
      expected = glm::rotate(expected, -glm::half_pi<float>(), glm::vec3(0, 0, 1));
      expected = glm::scale(expected, glm::vec3(0.5f, 0.25f, 1));
      expected = glm::inverse(expected);

      AssertExt::AreAlmostEqual(expected, Celeste::createInverseMatrix(glm::vec3(-2, 1, -1), -glm::half_pi<float>(), glm::vec3(2, 4, 1)));
    }
  };
}