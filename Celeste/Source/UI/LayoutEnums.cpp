#include "UI/LayoutEnums.h"
#include "Assert/Assert.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template <>
  std::string to_string(UI::HorizontalWrapMode horizontalWrapMode)
  {
    return horizontalWrapMode == UI::HorizontalWrapMode::kWrap ? "Wrap" : "Overflow";
  }

  //------------------------------------------------------------------------------------------------
  template<>
  bool from_string(const std::string& wrapModeString, UI::HorizontalWrapMode& wrapMode)
  {
    if (wrapModeString == "Wrap")
    {
      wrapMode = UI::HorizontalWrapMode::kWrap;
      return true;
    }
    else if (wrapModeString == "Overflow")
    {
      wrapMode = UI::HorizontalWrapMode::kOverflow;
      return true;
    }
    
    return false;
  }

  //------------------------------------------------------------------------------------------------
  template <>
  std::string to_string(UI::Orientation orientation)
  {
    return orientation == UI::Orientation::kHorizontal ? "Horizontal" : "Vertical";
  }

  //------------------------------------------------------------------------------------------------
  template <>
  std::string to_string(UI::HorizontalAlignment alignment)
  {
    switch (alignment)
    {
    case UI::HorizontalAlignment::kLeft:
      return "Left";

    case UI::HorizontalAlignment::kCentre:
      return "Centre";

    case UI::HorizontalAlignment::kRight:
      return "Right";

    default:
      ASSERT_FAIL();
      return "";
    }
  }

  //------------------------------------------------------------------------------------------------
  template <>
  std::string to_string(UI::VerticalAlignment alignment)
  {
    switch (alignment)
    {
    case UI::VerticalAlignment::kBottom:
      return "Bottom";

    case UI::VerticalAlignment::kCentre:
      return "Centre";

    case UI::VerticalAlignment::kTop:
      return "Top";

    default:
      ASSERT_FAIL();
      return "";
    }
  }
}