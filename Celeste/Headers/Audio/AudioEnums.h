#pragma once

#include "CelesteDllExport.h"
#include "Utils/ToString.h"

namespace Celeste
{
  namespace Audio
  {
    enum class AudioType
    {
      kMusic,
      kSFX
    };
  }

  //------------------------------------------------------------------------------------------------
  template<>
  inline std::string to_string(Audio::AudioType audio)
  {
    return audio == Audio::AudioType::kMusic ? "Music" : "SFX";
  }
}