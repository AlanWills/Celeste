#include "UtilityHeaders/UnitTestHeaders.h"

#include "UI/LayoutEnums.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestLayoutEnums)

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