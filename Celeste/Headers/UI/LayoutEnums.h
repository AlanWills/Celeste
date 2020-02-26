#pragma once

#include "CelesteDllExport.h"
#include "Utils/ToString.h"

#include <string>


namespace Celeste
{
  namespace UI
  {
    enum class Orientation
    {
      kHorizontal,
      kVertical,
    };

    enum class HorizontalAlignment
    {
      kLeft = 0,
      kCentre = 1,
      kRight = 2
    };

    enum class VerticalAlignment
    {
      kBottom = 0,
      kCentre = 1,
      kTop = 2,
    };
  }

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport std::string to_string(UI::Orientation orientation);

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport std::string to_string(UI::HorizontalAlignment alignment);

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport std::string to_string(UI::VerticalAlignment alignment);
}