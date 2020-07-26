#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "UI/LayoutEnums.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestLayoutEnums)

#pragma region Horizontal Wrap Mode To String Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalWrapMode_ToString_InputtingkWrap_ReturnsCorrectString)
  {
    Assert::AreEqual("Wrap", to_string(UI::HorizontalWrapMode::kWrap).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalWrapMode_ToString_InputtingkOverflow_ReturnsCorrectString)
  {
    Assert::AreEqual("Overflow", to_string(UI::HorizontalWrapMode::kOverflow).c_str());
  }

#pragma endregion

#pragma region Horizontal Wrap Mode From String Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalWrapMode_FromString_InputtingWrap_SetsOutputToCorrectValue)
  {
    UI::HorizontalWrapMode wrapMode = UI::HorizontalWrapMode::kOverflow;
    from_string("Wrap", wrapMode);

    Assert::IsTrue(UI::HorizontalWrapMode::kWrap == wrapMode);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalWrapMode_FromString_InputtingWrap_ReturnsTrue)
  {
    UI::HorizontalWrapMode wrapMode = UI::HorizontalWrapMode::kOverflow;

    Assert::IsTrue(from_string("Wrap", wrapMode));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalWrapMode_FromString_InputtingOverflow_SetsOutputToCorrectValue)
  {
    UI::HorizontalWrapMode wrapMode = UI::HorizontalWrapMode::kWrap;
    from_string("Overflow", wrapMode);

    Assert::IsTrue(UI::HorizontalWrapMode::kOverflow == wrapMode);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalWrapMode_FromString_InputtingOverflow_ReturnsTrue)
  {
    UI::HorizontalWrapMode wrapMode = UI::HorizontalWrapMode::kWrap;

    Assert::IsTrue(from_string("Overflow", wrapMode));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalWrapMode_FromString_InputtingEmptyString_DoesNotChangeValue)
  {
    UI::HorizontalWrapMode wrapMode = UI::HorizontalWrapMode::kWrap;
    from_string("", wrapMode);

    Assert::IsTrue(UI::HorizontalWrapMode::kWrap == wrapMode);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalWrapMode_FromString_InputtingEmptyString_ReturnsFalse)
  {
    UI::HorizontalWrapMode wrapMode = UI::HorizontalWrapMode::kWrap;

    Assert::IsFalse(from_string("", wrapMode));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalWrapMode_FromString_InputtingInvalidString_DoesNotChangeValue)
  {
    UI::HorizontalWrapMode wrapMode = UI::HorizontalWrapMode::kWrap;
    from_string("WubbaLubbaDubDub", wrapMode);

    Assert::IsTrue(UI::HorizontalWrapMode::kWrap == wrapMode);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalWrapMode_FromString_InputtingInvalidString_ReturnsFalse)
  {
    UI::HorizontalWrapMode wrapMode = UI::HorizontalWrapMode::kWrap;

    Assert::IsFalse(from_string("WubbaLubbaDubDub", wrapMode));
  }

#pragma endregion

#pragma region Orientation To String Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Orientation_ToString_InputtingkHorizontal_ReturnsCorrectString)
  {
    Assert::AreEqual("Horizontal", to_string(UI::Orientation::kHorizontal).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Orientation_ToString_InputtingkVertical_ReturnsCorrectString)
  {
    Assert::AreEqual("Vertical", to_string(UI::Orientation::kVertical).c_str());
  }

#pragma endregion

#pragma region Horizontal Alignment To String Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalAlignment_ToString_InputtingkLeft_ReturnsCorrectString)
  {
    Assert::AreEqual("Left", to_string(UI::HorizontalAlignment::kLeft).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalAlignment_ToString_InputtingkCentre_ReturnsCorrectString)
  {
    Assert::AreEqual("Centre", to_string(UI::HorizontalAlignment::kCentre).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HorizontalAlignment_ToString_InputtingkRight_ReturnsCorrectString)
  {
    Assert::AreEqual("Right", to_string(UI::HorizontalAlignment::kRight).c_str());
  }

#pragma endregion

#pragma region Vertical Alignment To String Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VerticalAlignment_ToString_InputtingkTop_ReturnsCorrectString)
  {
    Assert::AreEqual("Top", to_string(UI::VerticalAlignment::kTop).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VerticalAlignment_ToString_InputtingkCentre_ReturnsCorrectString)
  {
    Assert::AreEqual("Centre", to_string(UI::VerticalAlignment::kCentre).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VerticalAlignment_ToString_InputtingkBottom_ReturnsCorrectString)
  {
    Assert::AreEqual("Bottom", to_string(UI::VerticalAlignment::kBottom).c_str());
  }

#pragma endregion

  };
}