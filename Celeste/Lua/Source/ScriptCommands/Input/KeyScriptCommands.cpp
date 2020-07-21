#include "ScriptCommands/Input/KeyScriptCommands.h"
#include "sol/sol.hpp"

#include "GLFW/glfw3.h"


namespace Celeste::Lua::Input::KeyScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    bool isNumber(int glfwKey)
    {
      return GLFW_KEY_0 <= glfwKey && glfwKey <= GLFW_KEY_9;
    }

    //------------------------------------------------------------------------------------------------
    int getNumber(int glfwKey)
    {
      return isNumber(glfwKey) ? glfwKey - GLFW_KEY_0 : -1;
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    state.create_named_table(
      "Key",
      "isNumber", &Internals::isNumber,
      "getNumber", &Internals::getNumber,
      "Escape", GLFW_KEY_ESCAPE,
      "N", GLFW_KEY_N,
      "Num1", GLFW_KEY_1,
      "Num2", GLFW_KEY_2,
      "Num3", GLFW_KEY_3,
      "Num4", GLFW_KEY_4,
      "Num5", GLFW_KEY_5,
      "Num6", GLFW_KEY_6,
      "Num7", GLFW_KEY_7,
      "Num8", GLFW_KEY_8,
      "Num9", GLFW_KEY_9);
  }
}