#pragma once

#include "CelesteDllExport.h"
#include "Utils/ToString.h"

#include <string>


namespace Celeste
{
  namespace Input
  {
    enum class MouseButton
    {
      kLeft,
      kMiddle,
      kRight,
      kNumButtons,
    };

    enum class InputMode
    {
      kContinuous,   // The key must be down continuously
      kToggle   // When the key is pressed we toggle the visibility
    };

    enum class IncrementMode
    {
      kContinuous,
      kToggle
    };
  }

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport std::string to_string(Input::MouseButton mouseButton);

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport std::string to_string(Input::InputMode inputMode);

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport std::string to_string(Input::IncrementMode incrementMode);
}