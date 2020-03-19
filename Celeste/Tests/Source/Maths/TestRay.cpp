#include "UtilityHeaders/UnitTestHeaders.h"

#include "Maths/Ray.h"


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestRay)

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Ray_DefaultConstructor)
    {
      Celeste::Maths::Ray ray;

      Assert::IsTrue(glm::vec3() == ray.m_origin);
      Assert::IsTrue(glm::vec3(0, 0, -1) == ray.m_direction);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Ray_ConstructorWithOriginAndDirection)
    {
      Celeste::Maths::Ray ray(glm::vec3(15, -10, 0.001f), glm::vec3(66, 66.66f, -0.66f));

      Assert::IsTrue(glm::vec3(15, -10, 0.001f) == ray.m_origin);
      Assert::IsTrue(glm::vec3(66, 66.66f, -0.66f) == ray.m_direction);
    }
  };
}