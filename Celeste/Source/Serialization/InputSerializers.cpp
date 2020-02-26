#include "Serialization/InputSerializers.h"
#include "Input/Utils/GlfwKeyConverter.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template<>
  void serialize<Input::Key>(Input::Key key, std::string& output)
  {
    output.assign(Input::GlfwKeyConverter::getNameFromGlfwKey(key.m_key));
  }
}