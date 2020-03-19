#include "UtilityHeaders/UnitTestHeaders.h"

#include "Deserialization/UIDeserializers.h"

using namespace Celeste;
using namespace Celeste::UI;


namespace TestCeleste
{

  CELESTE_TEST_CLASS(TestHorizontalAlignmentConverter)

#pragma region Deserialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalAlignmentDeserializer_InputtingLeft_ReturnsTrue)
  {
    UI::HorizontalAlignment alignment;

    Assert::IsTrue(deserialize("Left", alignment));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalAlignmentDeserializer_Inputtingleft_ReturnsTrue)
  {
    UI::HorizontalAlignment alignment;

    Assert::IsTrue(deserialize("left", alignment));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalAlignmentDeserializer_InputtingLeft_SetsOutputTokLeft)
  {
    UI::HorizontalAlignment alignment;
    deserialize("Left", alignment);

    Assert::IsTrue(alignment == HorizontalAlignment::kLeft);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalAlignmentDeserializer_Inputtingleft_SetsOutputTokLeft)
  {
    UI::HorizontalAlignment alignment;
    deserialize("left", alignment);

    Assert::IsTrue(alignment == HorizontalAlignment::kLeft);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalAlignmentDeserializer_InputtingCentre_ReturnsTrue)
  {
    UI::HorizontalAlignment alignment;

    Assert::IsTrue(deserialize("Centre", alignment));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalAlignmentDeserializer_Inputtingcentre_ReturnsTrue)
  {
    UI::HorizontalAlignment alignment;

    Assert::IsTrue(deserialize("centre", alignment));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalAlignmentDeserializer_InputtingCentre_SetsOutputTokCentre)
  {
    UI::HorizontalAlignment alignment;
    deserialize("Centre", alignment);

    Assert::IsTrue(alignment == HorizontalAlignment::kCentre);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalAlignmentDeserializer_Inputtingcentre_SetsOutputTokCentre)
  {
    UI::HorizontalAlignment alignment;
    deserialize("centre", alignment);

    Assert::IsTrue(alignment == HorizontalAlignment::kCentre);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalAlignmentDeserializer_InputtingRight_ReturnsTrue)
  {
    UI::HorizontalAlignment alignment;

    Assert::IsTrue(deserialize("Right", alignment));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalAlignmentDeserializer_Inputtingright_ReturnsTrue)
  {
    UI::HorizontalAlignment alignment;

    Assert::IsTrue(deserialize("right", alignment));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalAlignmentDeserializer_InputtingRight_SetsOutputTokRight)
  {
    UI::HorizontalAlignment alignment;
    deserialize("Right", alignment);

    Assert::IsTrue(alignment == HorizontalAlignment::kRight);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalAlignmentDeserializer_Inputtingright_SetsOutputTokRight)
  {
    UI::HorizontalAlignment alignment;
    deserialize("right", alignment);

    Assert::IsTrue(alignment == HorizontalAlignment::kRight);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalAlignmentDeserializer_InputtingInvalidText_ReturnsFalse)
  {
    UI::HorizontalAlignment alignment;

    Assert::IsFalse(deserialize("", alignment));
    Assert::IsFalse(deserialize("Wdasada", alignment));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalAlignmentDeserializer_InputtingInvalidText_DoesNotChangeOutput)
  {
    UI::HorizontalAlignment alignment(HorizontalAlignment::kLeft);
    deserialize("", alignment);

    Assert::IsTrue(alignment == HorizontalAlignment::kLeft);

    deserialize("Wakdshas", alignment);

    Assert::IsTrue(alignment == HorizontalAlignment::kLeft);
  }

#pragma endregion

  };

}