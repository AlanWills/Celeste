#pragma once

#include "Media/VideoSettings.h"
#include "sol/sol.hpp"


namespace Celeste::Lua::Media::VideoScriptCommands
{
  const extern char* const AUTO_EXIT_SETTING_KEY;
  const extern char* const VOLUME_SETTING_KEY;
  const extern char* const ON_VIDEO_COMPLETE_SETTING_KEY;

  void initialize(sol::state& state);

  Celeste::Media::VideoSettings createVideoSettings(sol::table videoSettings);
}