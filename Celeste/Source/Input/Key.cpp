#include "Input/Key.h"
#include "Input/Utils/GlfwKeyConverter.h"


namespace Celeste
{
  std::string to_string(Input::Key key)
  {
    return std::move(Input::GlfwKeyConverter::getNameFromGlfwKey(key.m_key));
  }
}