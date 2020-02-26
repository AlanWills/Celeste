#include "Deserialization/InputDeserializers.h"
#include "Input/Utils/GlfwKeyConverter.h"
#include "UtilityHeaders/GLHeaders.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template<>
  bool deserialize<Input::IncrementMode>(const std::string& text, Input::IncrementMode& output)
  {
    if (text == "Toggle")
    {
      output = Input::IncrementMode::kToggle;
      return true;
    }
    else if (text == "Continuous")
    {
      output = Input::IncrementMode::kContinuous;
      return true;
    }

    ASSERT_FAIL();
    return false;
  }

  //------------------------------------------------------------------------------------------------
  template<>
  bool deserialize<Input::InputMode>(const std::string& text, Input::InputMode& output)
  {
    if (text == "Toggle")
    {
      output = Input::InputMode::kToggle;
      return true;
    }
    else if (text == "Continuous")
    {
      output = Input::InputMode::kContinuous;
      return true;
    }

    ASSERT_FAIL();
    return false;
  }

  //------------------------------------------------------------------------------------------------
  template<>
  bool deserialize<Input::Key>(const std::string& text, Input::Key& output)
  { 
    output.m_key = Input::GlfwKeyConverter::getGlfwKeyFromName(text);
    return output.m_key != GLFW_KEY_UNKNOWN;
  }
}