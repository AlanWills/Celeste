#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Deserialization/UIDeserializers.h"

using namespace Celeste;
using namespace Celeste::UI;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestOrientationDeserializer)

#pragma region Deserialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OrientationDeserializer_InputtingHorizontal_ReturnsTrue)
  {
    Orientation orientation;

    Assert::IsTrue(deserialize("Horizontal", orientation));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OrientationDeserializer_Inputtinghorizontal_ReturnsTrue)
  {
    Orientation orientation;

    Assert::IsTrue(deserialize("horizontal", orientation));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OrientationDeserializer_InputtingHorizontal_SetsOutput_TokHorizontal)
  {
    Orientation orientation;
    deserialize("Horizontal", orientation);

    Assert::IsTrue(orientation == Orientation::kHorizontal);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OrientationDeserializer_Inputtinghorizontal_SetsOutput_TokHorizontal)
  {
    Orientation orientation;
    deserialize("horizontal", orientation);

    Assert::IsTrue(orientation == Orientation::kHorizontal);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OrientationDeserializer_InputtingVertical_ReturnsTrue)
  {
    Orientation orientation;

    Assert::IsTrue(deserialize("Vertical", orientation));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OrientationDeserializer_Inputtingvertical_ReturnsTrue)
  {
    Orientation orientation;

    Assert::IsTrue(deserialize("vertical", orientation));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OrientationDeserializer_InputtingVertical_SetsOutput_TokVertical)
  {
    Orientation orientation;
    deserialize("Vertical", orientation);

    Assert::IsTrue(orientation == Orientation::kVertical);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OrientationDeserializer_Inputtingvertical_SetsOutput_TokVertical)
  {
    Orientation orientation;
    deserialize("vertical", orientation);

    Assert::IsTrue(orientation == Orientation::kVertical);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OrientationDeserializer_InputtingInvalidText_ReturnsFalse)
  {
    Orientation orientation;

    Assert::IsFalse(deserialize("", orientation));
    Assert::IsFalse(deserialize("waihdaosid", orientation));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OrientationDeserializer_InputtingInvalidText_DoesNotChangeOutput)
  {
    Orientation orientation(Orientation::kHorizontal);
    deserialize("", orientation);

    Assert::IsTrue(orientation == Orientation::kHorizontal);

    deserialize("Wubsada", orientation);

    Assert::IsTrue(orientation == Orientation::kHorizontal);
  }

#pragma endregion

  };
}