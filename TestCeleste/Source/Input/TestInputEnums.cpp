#include "UtilityHeaders/UnitTestHeaders.h"

#include "Input/InputEnums.h"


namespace TestCeleste
{
  namespace Input
  {
    CELESTE_TEST_CLASS(TestInputEnums)

#pragma region Mouse Button To String Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseButton_ToString_InputtingkLeft_ReturnsLeft)
    {
      Assert::AreEqual("Left", Celeste::to_string(Celeste::Input::MouseButton::kLeft).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseButton_ToString_InputtingkMiddle_ReturnsMiddle)
    {
      Assert::AreEqual("Middle", Celeste::to_string(Celeste::Input::MouseButton::kMiddle).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseButton_ToString_InputtingkRight_ReturnsLeft)
    {
      Assert::AreEqual("Right", Celeste::to_string(Celeste::Input::MouseButton::kRight).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseButton_ToString_InputtingOtherValue_ReturnsEmptyString)
    {
      Assert::IsTrue(Celeste::to_string(Celeste::Input::MouseButton::kNumButtons).empty());
    }

#pragma endregion

#pragma region Input Mode To String Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputMode_ToString_InputtingkContinuous_ReturnsContinuous)
    {
      Assert::AreEqual("Continuous", Celeste::to_string(Celeste::Input::InputMode::kContinuous).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(InputMode_ToString_InputtingkToggle_ReturnsToggle)
    {
      Assert::AreEqual("Toggle", Celeste::to_string(Celeste::Input::InputMode::kToggle).c_str());
    }

#pragma endregion

#pragma region Increment Mode To String Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IncrementMode_ToString_InputtingkToggle_ReturnsToggle)
    {
      Assert::AreEqual("Toggle", Celeste::to_string(Celeste::Input::InputMode::kToggle).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IncrementMode_ToString_InputtingkContinuous_ReturnsContinuous)
    {
      Assert::AreEqual("Continuous", Celeste::to_string(Celeste::Input::InputMode::kContinuous).c_str());
    }

#pragma endregion

    };
  }
}