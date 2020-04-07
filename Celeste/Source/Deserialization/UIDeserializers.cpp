#include "Deserialization/UIDeserializers.h"
#include "Assert/Assert.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template <>
  bool deserialize<UI::HorizontalAlignment>(const std::string& text, UI::HorizontalAlignment& output)
  {
    if (text.empty())
    {
      ASSERT_FAIL();
      return false;
    }

    if ((text.front() == 'l' || text.front() == 'L') &&
      text.substr(1) == "eft")
    {
      output = UI::HorizontalAlignment::kLeft;
      return true;
    }
    else if ((text.front() == 'c' || text.front() == 'C') &&
      text.substr(1) == "entre")
    {
      output = UI::HorizontalAlignment::kCentre;
      return true;
    }
    else if ((text.front() == 'r' || text.front() == 'R') &&
      text.substr(1) == "ight")
    {
      output = UI::HorizontalAlignment::kRight;
      return true;
    }

    ASSERT_FAIL();
    return false;
  }

  //------------------------------------------------------------------------------------------------
  template <>
  bool deserialize<UI::VerticalAlignment>(const std::string& text, UI::VerticalAlignment& output)
  {
    if (text.empty())
    {
      ASSERT_FAIL();
      return false;
    }

    if ((text.front() == 'b' || text.front() == 'B') &&
      text.substr(1) == "ottom")
    {
      output = UI::VerticalAlignment::kBottom;
      return true;
    }
    else if ((text.front() == 'c' || text.front() == 'C') &&
      text.substr(1) == "entre")
    {
      output = UI::VerticalAlignment::kCentre;
      return true;
    }
    else if ((text.front() == 't' || text.front() == 'T') &&
      text.substr(1) == "op")
    {
      output = UI::VerticalAlignment::kTop;
      return true;
    }

    ASSERT_FAIL();
    return false;
  }

  //------------------------------------------------------------------------------------------------
  template <>
  bool deserialize<UI::Orientation>(const std::string& text, UI::Orientation& output)
  {
    if (text.empty())
    {
      ASSERT_FAIL();
      return false;
    }

    if ((text.front() == 'v' || text.front() == 'V') &&
      text.substr(1) == "ertical")
    {
      output = UI::Orientation::kVertical;
      return true;
    }
    else if ((text.front() == 'h' || text.front() == 'H') &&
      text.substr(1) == "orizontal")
    {
      output = UI::Orientation::kHorizontal;
      return true;
    }

    ASSERT_FAIL();
    return false;
  }
}