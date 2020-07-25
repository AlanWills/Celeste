#include "Input/Utils/GlfwKeyConverter.h"
#include "UtilityHeaders/GLHeaders.h"


namespace Celeste
{
  namespace Input
  {
    //---------------------------------------------------------------
    // Initialize the static lookups with all the expected values
    //---------------------------------------------------------------


    //---------------------------------------------------------------
    std::unordered_map<char, int> GlfwKeyConverter::m_charToNumberLookup = 
    {
      { ' ', GLFW_KEY_SPACE },
      { '\'', GLFW_KEY_APOSTROPHE },
      { ',', GLFW_KEY_COMMA },
      { '-', GLFW_KEY_MINUS },
      { '.', GLFW_KEY_PERIOD },
      { '/', GLFW_KEY_SLASH },
      { '0', GLFW_KEY_0 },
      { '1', GLFW_KEY_1 },
      { '2', GLFW_KEY_2 },
      { '3', GLFW_KEY_3 },
      { '4', GLFW_KEY_4 },
      { '5', GLFW_KEY_5 },
      { '6', GLFW_KEY_6 },
      { '7', GLFW_KEY_7 },
      { '8', GLFW_KEY_8 },
      { '9', GLFW_KEY_9 },
      { ';', GLFW_KEY_SEMICOLON },
      { '=', GLFW_KEY_EQUAL },
      { 'a', GLFW_KEY_A },
      { 'A', GLFW_KEY_A },
      { 'b', GLFW_KEY_B },
      { 'B', GLFW_KEY_B },
      { 'c', GLFW_KEY_C },
      { 'C', GLFW_KEY_C },
      { 'd', GLFW_KEY_D },
      { 'D', GLFW_KEY_D },
      { 'e', GLFW_KEY_E },
      { 'E', GLFW_KEY_E },
      { 'f', GLFW_KEY_F },
      { 'F', GLFW_KEY_F },
      { 'g', GLFW_KEY_G },
      { 'G', GLFW_KEY_G },
      { 'h', GLFW_KEY_H },
      { 'H', GLFW_KEY_H },
      { 'i', GLFW_KEY_I },
      { 'I', GLFW_KEY_I },
      { 'j', GLFW_KEY_J },
      { 'J', GLFW_KEY_J },
      { 'k', GLFW_KEY_K },
      { 'K', GLFW_KEY_K },
      { 'l', GLFW_KEY_L },
      { 'L', GLFW_KEY_L },
      { 'm', GLFW_KEY_M },
      { 'M', GLFW_KEY_M },
      { 'n', GLFW_KEY_N },
      { 'N', GLFW_KEY_N },
      { 'o', GLFW_KEY_O },
      { 'O', GLFW_KEY_O },
      { 'p', GLFW_KEY_P },
      { 'P', GLFW_KEY_P },
      { 'q', GLFW_KEY_Q },
      { 'Q', GLFW_KEY_Q },
      { 'r', GLFW_KEY_R },
      { 'R', GLFW_KEY_R },
      { 's', GLFW_KEY_S },
      { 'S', GLFW_KEY_S },
      { 't', GLFW_KEY_T },
      { 'T', GLFW_KEY_T },
      { 'u', GLFW_KEY_U },
      { 'U', GLFW_KEY_U },
      { 'v', GLFW_KEY_V },
      { 'V', GLFW_KEY_V },
      { 'w', GLFW_KEY_W },
      { 'W', GLFW_KEY_W },
      { 'x', GLFW_KEY_X },
      { 'X', GLFW_KEY_X },
      { 'y', GLFW_KEY_Y },
      { 'Y', GLFW_KEY_Y },
      { 'z', GLFW_KEY_Z },
      { 'Z', GLFW_KEY_Z },
      { '[', GLFW_KEY_LEFT_BRACKET },
      { '\\', GLFW_KEY_BACKSLASH },
      { ']', GLFW_KEY_RIGHT_BRACKET },
      { '`', GLFW_KEY_GRAVE_ACCENT },
    };

    //---------------------------------------------------------------
    std::unordered_map<std::string, int> GlfwKeyConverter::m_stringToNumberLookup =
    {
      { "space", GLFW_KEY_SPACE },
      { "esc", GLFW_KEY_ESCAPE },
      { "escape", GLFW_KEY_ESCAPE },
      { "enter", GLFW_KEY_ENTER },
      { "tab", GLFW_KEY_TAB },
      { "backspace", GLFW_KEY_BACKSPACE },
      { "insert", GLFW_KEY_INSERT },
      { "delete", GLFW_KEY_DELETE },
      { "right", GLFW_KEY_RIGHT },
      { "left", GLFW_KEY_LEFT },
      { "down", GLFW_KEY_DOWN },
      { "up", GLFW_KEY_UP },
      { "page up", GLFW_KEY_PAGE_UP },
      { "page down", GLFW_KEY_PAGE_DOWN },
      { "home", GLFW_KEY_HOME },
      { "end", GLFW_KEY_END },
      { "caps lock", GLFW_KEY_CAPS_LOCK },
      { "scroll lock", GLFW_KEY_SCROLL_LOCK },
      { "num lock", GLFW_KEY_NUM_LOCK },
      { "print screen", GLFW_KEY_PRINT_SCREEN },
      { "pause", GLFW_KEY_PAUSE },
      { "F1", GLFW_KEY_F1 },
      { "F2", GLFW_KEY_F2 },
      { "F3", GLFW_KEY_F3 },
      { "F4", GLFW_KEY_F4 },
      { "F5", GLFW_KEY_F5 },
      { "F6", GLFW_KEY_F6 },
      { "F7", GLFW_KEY_F7 },
      { "F8", GLFW_KEY_F8 },
      { "F9", GLFW_KEY_F9 },
      { "F10", GLFW_KEY_F10 },
      { "F11", GLFW_KEY_F11 },
      { "F12", GLFW_KEY_F12 },
      { "left shift", GLFW_KEY_LEFT_SHIFT },
      { "shift", GLFW_KEY_LEFT_SHIFT },
      { "left control", GLFW_KEY_LEFT_CONTROL },
      { "left ctrl", GLFW_KEY_LEFT_CONTROL },
      { "control", GLFW_KEY_LEFT_CONTROL },
      { "ctrl", GLFW_KEY_LEFT_CONTROL },
      { "left alt", GLFW_KEY_LEFT_ALT },
      { "alt", GLFW_KEY_LEFT_ALT },
      { "right shift", GLFW_KEY_RIGHT_SHIFT },
      { "right control", GLFW_KEY_RIGHT_CONTROL },
      { "right ctrl", GLFW_KEY_RIGHT_CONTROL },
      { "right alt", GLFW_KEY_RIGHT_ALT },
    };

    //---------------------------------------------------------------
    std::unordered_map<int, const char*> GlfwKeyConverter::m_intToNameLookup =
    {
      { GLFW_KEY_SPACE, " " },
      { GLFW_KEY_APOSTROPHE, "'" },
      { GLFW_KEY_COMMA, "," },
      { GLFW_KEY_MINUS, "-" },
      { GLFW_KEY_PERIOD, "." },
      { GLFW_KEY_SLASH, "/" },
      { GLFW_KEY_SEMICOLON, ";" },
      { GLFW_KEY_EQUAL, "=" },
      { GLFW_KEY_LEFT_BRACKET, "(" },
      { GLFW_KEY_BACKSLASH, "\\" },
      { GLFW_KEY_RIGHT_BRACKET, ")" },
      { GLFW_KEY_GRAVE_ACCENT, "`" },
      { GLFW_KEY_0, "0" },
      { GLFW_KEY_1, "1" },
      { GLFW_KEY_2, "2" },
      { GLFW_KEY_3, "3" },
      { GLFW_KEY_4, "4" },
      { GLFW_KEY_5, "5" },
      { GLFW_KEY_6, "6" },
      { GLFW_KEY_7, "7" },
      { GLFW_KEY_8, "8" },
      { GLFW_KEY_9, "9" },
      { GLFW_KEY_A, "A" },
      { GLFW_KEY_B, "B" },
      { GLFW_KEY_C, "C" },
      { GLFW_KEY_D, "D" },
      { GLFW_KEY_E, "E" },
      { GLFW_KEY_F, "F" },
      { GLFW_KEY_G, "G" },
      { GLFW_KEY_H, "H" },
      { GLFW_KEY_I, "I" },
      { GLFW_KEY_J, "J" },
      { GLFW_KEY_K, "K" },
      { GLFW_KEY_L, "L" },
      { GLFW_KEY_M, "M" },
      { GLFW_KEY_N, "N" },
      { GLFW_KEY_O, "O" },
      { GLFW_KEY_P, "P" },
      { GLFW_KEY_Q, "Q" },
      { GLFW_KEY_R, "R" },
      { GLFW_KEY_S, "S" },
      { GLFW_KEY_T, "T" },
      { GLFW_KEY_U, "U" },
      { GLFW_KEY_V, "V" },
      { GLFW_KEY_W, "W" },
      { GLFW_KEY_X, "X" },
      { GLFW_KEY_Y, "Y" },
      { GLFW_KEY_Z, "Z" },
      { GLFW_KEY_ESCAPE, "escape" },
      { GLFW_KEY_ENTER, "enter" },
      { GLFW_KEY_TAB, "tab" },
      { GLFW_KEY_BACKSPACE, "backspace" },
      { GLFW_KEY_INSERT, "insert" },
      { GLFW_KEY_DELETE, "delete" },
      { GLFW_KEY_RIGHT, "right" },
      { GLFW_KEY_LEFT, "left" },
      { GLFW_KEY_DOWN, "down" },
      { GLFW_KEY_UP, "up" },
      { GLFW_KEY_PAGE_UP, "page up" },
      { GLFW_KEY_PAGE_DOWN, "page down" },
      { GLFW_KEY_HOME, "home" },
      { GLFW_KEY_END, "end" },
      { GLFW_KEY_CAPS_LOCK, "caps lock" },
      { GLFW_KEY_SCROLL_LOCK, "scroll lock" },
      { GLFW_KEY_NUM_LOCK, "num lock" },
      { GLFW_KEY_PRINT_SCREEN, "print screen" },
      { GLFW_KEY_PAUSE, "pause" },
      { GLFW_KEY_F1, "F1" },
      { GLFW_KEY_F2, "F2" },
      { GLFW_KEY_F3, "F3" },
      { GLFW_KEY_F4, "F4" },
      { GLFW_KEY_F5, "F5" },
      { GLFW_KEY_F6, "F6" },
      { GLFW_KEY_F7, "F7" },
      { GLFW_KEY_F8, "F8" },
      { GLFW_KEY_F9, "F9" },
      { GLFW_KEY_F10, "F10" },
      { GLFW_KEY_F11, "F11" },
      { GLFW_KEY_F12, "F12" },
      { GLFW_KEY_LEFT_SHIFT, "left shift" },
      { GLFW_KEY_LEFT_CONTROL, "left control" },
      { GLFW_KEY_LEFT_ALT, "left alt" },
      { GLFW_KEY_RIGHT_SHIFT, "right shift" },
      { GLFW_KEY_RIGHT_CONTROL, "right control" },
      { GLFW_KEY_RIGHT_CONTROL, "right ctrl" },
      { GLFW_KEY_RIGHT_ALT, "right alt" },
    };

    //---------------------------------------------------------------
    int GlfwKeyConverter::getGlfwKeyFromName(const std::string& keyName)
    {
      if (keyName.empty())
      {
        // Invalid input, so return the unknown key value
        return GLFW_KEY_UNKNOWN;
      }
      else if (keyName.size() == 1)
      {
        // We have actually entered a char, so search through the char lookup
        return m_charToNumberLookup.find(keyName[0]) != m_charToNumberLookup.end() ? m_charToNumberLookup[keyName[0]] : GLFW_KEY_UNKNOWN;
      }
      else
      {
        // We have entered a full string, so search through the string lookup
        return m_stringToNumberLookup.find(keyName) != m_stringToNumberLookup.end() ? m_stringToNumberLookup[keyName] : GLFW_KEY_UNKNOWN;
      }
    }
    
    //---------------------------------------------------------------
    std::string GlfwKeyConverter::getNameFromGlfwKey(int glfwKey)
    {
      return m_intToNameLookup.find(glfwKey) != m_intToNameLookup.end() ? m_intToNameLookup[glfwKey] : "";
    }
  }
}