#pragma once

#include "Deserializers.h"
#include "Input/Key.h"
#include "Input/InputEnums.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport bool deserialize<Input::IncrementMode>(const std::string& text, Input::IncrementMode& output);

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport bool deserialize<Input::InputMode>(const std::string& text, Input::InputMode& output);

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport bool deserialize<Input::Key>(const std::string& text, Input::Key& output);
}