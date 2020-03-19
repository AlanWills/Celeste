#include "UtilityHeaders/UnitTestHeaders.h"

#include "Maths/Vector.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestVector)

#pragma region Length Squared Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Vector_LengthSquared_ZeroVector_ReturnsZero)
    {
      glm::vec3 zero;

      Assert::AreEqual(0.0f, zero.x);
      Assert::AreEqual(0.0f, zero.y);
      Assert::AreEqual(0.0f, zero.z);
      Assert::AreEqual(0.0f, Maths::length_squared(zero));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Vector_LengthSquared_NonZeroVector_ReturnsComponentSumSquared)
    {
      glm::vec3 v(10, 0.1f, -0.35f);

      Assert::AreEqual(10 * 10 + 0.1f * 0.1f + -0.35f * -0.35f, Maths::length_squared(v));
    }

#pragma endregion
  };
}