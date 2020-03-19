#include "UtilityHeaders/UnitTestHeaders.h"

#include "Maths/MathsUtils.h"
#include "UtilityHeaders/GLHeaders.h"


namespace TestCeleste
{
  namespace Maths
  {
    CELESTE_TEST_CLASS(TestMathsUtils)

#pragma region Look At Tests

#pragma region Vec2 Overload

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MathsUtils_LookAt_Vec2Overload_TargetPositionSameAsCurrentPosition_ReturnsZero)
    {
      Assert::AreEqual(0.0f, Celeste::Maths::lookAt(glm::vec3(1, 1, 1), glm::vec2(1, 1)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MathsUtils_LookAt_Vec2Overload_TargetPositionDifferentToCurrentPosition_ReturnsCorrectAngle)
    {
      Assert::AreEqual(0.0f, Celeste::Maths::lookAt(glm::vec3(1, 1, 1), glm::vec2(1, 2)));
      Assert::AreEqual(glm::half_pi<float>(), Celeste::Maths::lookAt(glm::vec3(1, 1, 1), glm::vec2(2, 1)));
      Assert::AreEqual(glm::pi<float>(), Celeste::Maths::lookAt(glm::vec3(1, 1, 1), glm::vec2(1, 0)));
      Assert::AreEqual(-glm::half_pi<float>(), Celeste::Maths::lookAt(glm::vec3(1, 1, 1), glm::vec2(0, 1)));
    }

#pragma endregion

#pragma region Vec3 Overload

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MathsUtils_LookAt_Vec3Overload_TargetPositionSameAsCurrentPosition_ReturnsZero)
    {
      Assert::AreEqual(0.0f, Celeste::Maths::lookAt(glm::vec3(1, 1, 1), glm::vec3(1, 1, 1)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MathsUtils_LookAt_Vec3Overload_TargetPositionDifferentToCurrentPosition_ReturnsCorrectAngle)
    {
      Assert::AreEqual(0.0f, Celeste::Maths::lookAt(glm::vec3(1, 1, 1), glm::vec3(1, 2, 1)));
      Assert::AreEqual(glm::half_pi<float>(), Celeste::Maths::lookAt(glm::vec3(1, 1, 1), glm::vec3(2, 1, 1)));
      Assert::AreEqual(glm::pi<float>(), Celeste::Maths::lookAt(glm::vec3(1, 1, 1), glm::vec3(1, 0, 1)));
      Assert::AreEqual(-glm::half_pi<float>(), Celeste::Maths::lookAt(glm::vec3(1, 1, 1), glm::vec3(0, 1, 1)));
    }

#pragma endregion

#pragma endregion

    };
  }
}