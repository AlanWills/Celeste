#pragma once

#include "CelesteDllExport.h"
#include "Media/VideoSettings.h"
#include "sol/sol.hpp"


namespace Celeste::Lua::Media::VideoScriptCommands
{
  CelesteDllExport const extern char* const AUTO_EXIT_SETTING_KEY;
  CelesteDllExport const extern char* const VOLUME_SETTING_KEY;
  CelesteDllExport const extern char* const ON_VIDEO_COMPLETE_SETTING_KEY;

  CelesteDllExport void initialize();
  CelesteDllExport Celeste::Media::VideoSettings createVideoSettings(sol::table videoSettings);
}