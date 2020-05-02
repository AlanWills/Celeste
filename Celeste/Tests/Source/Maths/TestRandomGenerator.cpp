#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Maths/RandomGenerator.h"

using namespace Celeste;


namespace TestCeleste
{

  CELESTE_TEST_CLASS(TestRandomGenerator)

#pragma region Generate Float Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RandomGenerator_GenerateFloat)
    {
      float result = Random::generate(0.0f, 1.0f);
      Assert::IsTrue(0 <= result);
      Assert::IsTrue(result <= 1);

      result = Random::generate(-10.0f, 10.0f);
      Assert::IsTrue(-10 <= result);
      Assert::IsTrue(result <= 10);

      result = Random::generate(0.0f, 0.0f);
      Assert::AreEqual(0.0f, result);
    }

#pragma endregion

#pragma region Generate Size_t Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(RandomGenerator_GenerateSize_t)
    {
      size_t result = Random::generate((size_t)0, 1);
      Assert::IsTrue(0 <= result);
      Assert::IsTrue(result <= 1);

      /*result = Random::generate((size_t)10, 14);
      Assert::IsTrue(10 <= result);
      Assert::IsTrue(result <= 14);

      result = Random::generate((size_t)1, 1);
      Assert::AreEqual((size_t)1, result);*/
    }

#pragma endregion

  };
}