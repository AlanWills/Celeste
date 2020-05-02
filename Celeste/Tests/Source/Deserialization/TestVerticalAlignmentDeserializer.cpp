#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Deserialization/UIDeserializers.h"

using namespace Celeste;
using namespace Celeste::UI;


namespace TestCeleste
{

  CELESTE_TEST_CLASS(TestVerticalAlignmentConverter)

#pragma region Deserialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VerticalAlignmentDeserializer_InputtingBottom_ReturnsTrue)
  {
    UI::VerticalAlignment alignment;

    Assert::IsTrue(deserialize("Bottom", alignment));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VerticalAlignmentDeserializer_Inputtingbottom_ReturnsTrue)
  {
    UI::VerticalAlignment alignment;

    Assert::IsTrue(deserialize("bottom", alignment));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VerticalAlignmentDeserializer_InputtingBottom_SetsOutputTokBottom)
  {
    UI::VerticalAlignment alignment;
    deserialize("Bottom", alignment);

    Assert::IsTrue(alignment == VerticalAlignment::kBottom);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VerticalAlignmentDeserializer_Inputtingbottom_SetsOutputTokBottom)
  {
    UI::VerticalAlignment alignment;
    deserialize("bottom", alignment);

    Assert::IsTrue(alignment == VerticalAlignment::kBottom);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VerticalAlignmentDeserializer_InputtingCentre_ReturnsTrue)
  {
    UI::VerticalAlignment alignment;

    Assert::IsTrue(deserialize("Centre", alignment));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VerticalAlignmentDeserializer_Inputtingcentre_ReturnsTrue)
  {
    UI::VerticalAlignment alignment;

    Assert::IsTrue(deserialize("centre", alignment));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VerticalAlignmentDeserializer_InputtingCentre_SetsOutputTokCentre)
  {
    UI::VerticalAlignment alignment;
    deserialize("Centre", alignment);

    Assert::IsTrue(alignment == VerticalAlignment::kCentre);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VerticalAlignmentDeserializer_Inputtingcentre_SetsOutputTokCentre)
  {
    UI::VerticalAlignment alignment;
    deserialize("centre", alignment);

    Assert::IsTrue(alignment == VerticalAlignment::kCentre);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VerticalAlignmentDeserializer_InputtingTop_ReturnsTrue)
  {
    UI::VerticalAlignment alignment;

    Assert::IsTrue(deserialize("Top", alignment));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VerticalAlignmentDeserializer_Inputtingtop_ReturnsTrue)
  {
    UI::VerticalAlignment alignment;

    Assert::IsTrue(deserialize("top", alignment));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VerticalAlignmentDeserializer_InputtingTop_SetsOutputTokTop)
  {
    UI::VerticalAlignment alignment;
    deserialize("Top", alignment);

    Assert::IsTrue(alignment == VerticalAlignment::kTop);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VerticalAlignmentDeserializer_Inputtingtop_SetsOutputTokTop)
  {
    UI::VerticalAlignment alignment;
    deserialize("top", alignment);

    Assert::IsTrue(alignment == VerticalAlignment::kTop);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VerticalAlignmentDeserializer_InputtingInvalidText_ReturnsFalse)
  {
    UI::VerticalAlignment alignment;

    Assert::IsFalse(deserialize("", alignment));
    Assert::IsFalse(deserialize("Wdasada", alignment));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VerticalAlignmentDeserializer_InputtingInvalidText_DoesNotChangeOutput)
  {
    UI::VerticalAlignment alignment(VerticalAlignment::kBottom);
    deserialize("", alignment);

    Assert::IsTrue(alignment == VerticalAlignment::kBottom);

    deserialize("Wakdshas", alignment);

    Assert::IsTrue(alignment == VerticalAlignment::kBottom);
  }

#pragma endregion

};

}