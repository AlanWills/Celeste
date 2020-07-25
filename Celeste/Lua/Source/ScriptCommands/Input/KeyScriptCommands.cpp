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
      "Space", GLFW_KEY_SPACE,
      "Apostrophe", GLFW_KEY_APOSTROPHE,
      "Comma", GLFW_KEY_COMMA,
      "Minus", GLFW_KEY_MINUS,
      "Period", GLFW_KEY_PERIOD,
      "ForwardSlash", GLFW_KEY_SLASH,
      "SemiColon", GLFW_KEY_SEMICOLON,
      "Equals", GLFW_KEY_EQUAL,
      "LeftBracket", GLFW_KEY_LEFT_BRACKET,
      "Backslash", GLFW_KEY_BACKSLASH,
      "RightBracket", GLFW_KEY_RIGHT_BRACKET,
      "GraveAccent", GLFW_KEY_GRAVE_ACCENT,
      "Num0", GLFW_KEY_0,
      "Num1", GLFW_KEY_1,
      "Num2", GLFW_KEY_2,
      "Num3", GLFW_KEY_3,
      "Num4", GLFW_KEY_4,
      "Num5", GLFW_KEY_5,
      "Num6", GLFW_KEY_6,
      "Num7", GLFW_KEY_7,
      "Num8", GLFW_KEY_8,
      "Num9", GLFW_KEY_9,
      "A", GLFW_KEY_A,
      "B", GLFW_KEY_B,
      "C", GLFW_KEY_C,
      "D", GLFW_KEY_D,
      "E", GLFW_KEY_E,
      "F", GLFW_KEY_F,
      "G", GLFW_KEY_G,
      "H", GLFW_KEY_H,
      "I", GLFW_KEY_I,
      "J", GLFW_KEY_J,
      "K", GLFW_KEY_K,
      "L", GLFW_KEY_L,
      "M", GLFW_KEY_M,
      "N", GLFW_KEY_N,
      "O", GLFW_KEY_O,
      "P", GLFW_KEY_P,
      "Q", GLFW_KEY_Q,
      "R", GLFW_KEY_R,
      "S", GLFW_KEY_S,
      "T", GLFW_KEY_T,
      "U", GLFW_KEY_U,
      "V", GLFW_KEY_V,
      "W", GLFW_KEY_W,
      "X", GLFW_KEY_X,
      "Y", GLFW_KEY_Y,
      "Z", GLFW_KEY_Z,
      "Escape", GLFW_KEY_ESCAPE,
      "Enter", GLFW_KEY_ENTER,
      "Tab", GLFW_KEY_TAB,
      "Backspace", GLFW_KEY_BACKSPACE,
      "Insert", GLFW_KEY_INSERT,
      "Delete", GLFW_KEY_DELETE,
      "Right", GLFW_KEY_RIGHT,
      "Left", GLFW_KEY_LEFT,
      "Down", GLFW_KEY_DOWN,
      "Up", GLFW_KEY_UP,
      "PageUp", GLFW_KEY_PAGE_UP,
      "PageDown", GLFW_KEY_PAGE_DOWN,
      "Home", GLFW_KEY_HOME,
      "End", GLFW_KEY_END,
      "CapsLock", GLFW_KEY_CAPS_LOCK,
      "ScrollLock", GLFW_KEY_SCROLL_LOCK,
      "NumLock", GLFW_KEY_NUM_LOCK,
      "PrintScreen", GLFW_KEY_PRINT_SCREEN,
      "Pause", GLFW_KEY_PAUSE,
      "F1", GLFW_KEY_F1,
      "F2", GLFW_KEY_F2,
      "F3", GLFW_KEY_F3,
      "F4", GLFW_KEY_F4,
      "F5", GLFW_KEY_F5,
      "F6", GLFW_KEY_F6,
      "F7", GLFW_KEY_F7,
      "F8", GLFW_KEY_F8,
      "F9", GLFW_KEY_F9,
      "F10", GLFW_KEY_F10,
      "F11", GLFW_KEY_F11,
      "F12", GLFW_KEY_F12,
      "LeftShift", GLFW_KEY_LEFT_SHIFT,
      "LeftControl", GLFW_KEY_LEFT_CONTROL,
      "LeftAlt", GLFW_KEY_LEFT_ALT,
      "RightShift", GLFW_KEY_RIGHT_SHIFT,
      "RightControl", GLFW_KEY_RIGHT_CONTROL,
      "RightAlt", GLFW_KEY_RIGHT_ALT);
  }
}