#include "UtilityHeaders/UnitTestHeaders.h"

#include "Maths/MathsEnums.h"


namespace TestCeleste
{
  namespace Maths
  {

    CELESTE_TEST_CLASS(TestMathsEnums)

#pragma region Space To String Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Space_ToString_InputtingkWorld_ReturnsWorld)
    {
      Assert::AreEqual("World", Celeste::to_string(Celeste::Maths::Space::kWorld).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Space_ToString_InputtingkLocal_ReturnsLocal)
    {
      Assert::AreEqual("Local", Celeste::to_string(Celeste::Maths::Space::kLocal).c_str());
    }

#pragma endregion

    };
  }
}