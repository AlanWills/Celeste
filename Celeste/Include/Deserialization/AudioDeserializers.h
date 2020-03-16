#pragma once

#include "Deserializers.h"
#include "Audio/AudioEnums.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport bool deserialize<Audio::AudioType>(const std::string& text, Audio::AudioType& output);
}