#pragma once

#include "CelesteDllExport.h"
#include "UtilityHeaders/GLHeaders.h"


namespace Celeste
{
  namespace Input
  {
    struct Key
    {
      Key() : Key(GLFW_KEY_UNKNOWN) { }
      Key(int glfwKey) : m_key(glfwKey) { }

      int m_key;
    };
  }

  //------------------------------------------------------------------------------------------------
  CelesteDllExport std::string to_string(Input::Key key);
}