#pragma once

#include "Deserializers.h"
#include "UI/LayoutEnums.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport bool deserialize<UI::HorizontalAlignment>(const std::string& text, UI::HorizontalAlignment& output);

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport bool deserialize<UI::VerticalAlignment>(const std::string& text, UI::VerticalAlignment& output);

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport bool deserialize<UI::Orientation>(const std::string& text, UI::Orientation& output);
}