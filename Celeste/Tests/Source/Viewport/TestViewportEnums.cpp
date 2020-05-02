#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Viewport/ViewportEnums.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestViewportEnums)

#pragma region ProjectionMode To String Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProjectionMode_ToString_InputtingkOrthographic_ReturnsCorrectString)
  {
    Assert::AreEqual("Orthographic", to_string(ProjectionMode::kOrthographic).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Orientation_ToString_InputtingkPerspective_ReturnsCorrectString)
  {
    Assert::AreEqual("Perspective", to_string(ProjectionMode::kPerspective).c_str());
  }

#pragma endregion

  };
}