#include "Input/InputEnums.h"
#include "Assert/Assert.h"

#include <string>


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template<>
  std::string to_string(Input::MouseButton mouseButton)
  {
    if (mouseButton == Input::MouseButton::kLeft)
    {
      return "Left";
    }
    else if (mouseButton == Input::MouseButton::kMiddle)
    {
      return "Middle";
    }
    else if (mouseButton == Input::MouseButton::kRight)
    {
      return "Right";
    }
    else
    {
      ASSERT_FAIL();
      return "";
    }
  }

  //------------------------------------------------------------------------------------------------
  template<>
  std::string to_string(Input::InputMode inputMode)
  {
    if (inputMode == Input::InputMode::kToggle)
    {
      return "Toggle";
    }
    else if (inputMode == Input::InputMode::kContinuous)
    {
      return "Continuous";
    }
    else
    {
      ASSERT_FAIL();
      return "";
    }
  }

  //------------------------------------------------------------------------------------------------
  template<>
  std::string to_string(Input::IncrementMode incrementMode)
  {
    if (incrementMode == Input::IncrementMode::kToggle)
    {
      return "Toggle";
    }
    else if (incrementMode == Input::IncrementMode::kContinuous)
    {
      return "Continuous";
    }
    else
    {
      ASSERT_FAIL();
      return "";
    }
  }
}