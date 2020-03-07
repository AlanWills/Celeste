#include "Events/TriggerMode.h"
#include "Debug/Assert.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template<>
  std::string to_string(Events::TriggerMode triggerMode)
  {
    if (triggerMode == Events::TriggerMode::kOnce)
    {
      return "Once";
    }
    else if (triggerMode == Events::TriggerMode::kUnlimited)
    {
      return "Unlimited";
    }
    else
    {
      ASSERT_FAIL();
      return "";
    }
  }

  //------------------------------------------------------------------------------------------------
  template<>
  bool from_string(const std::string& text, Events::TriggerMode& triggerMode)
  {
    if (text == "Once")
    {
      triggerMode = Events::TriggerMode::kOnce;
      return true;
    }
    else if (text == "Unlimited")
    {
      triggerMode = Events::TriggerMode::kUnlimited;
      return true;
    }
    else
    {
      ASSERT_FAIL();
      return false;
    }
  }
}