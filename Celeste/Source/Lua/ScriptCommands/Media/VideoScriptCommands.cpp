#include "Lua/ScriptCommands/Media/VideoScriptCommands.h"
#include "Lua/LuaState.h"

#include "Media/Video.h"


namespace Celeste::Lua::Media::VideoScriptCommands
{
  //------------------------------------------------------------------------------------------------
  const char* const AUTO_EXIT_SETTING_KEY = "AutoExit";
  const char* const VOLUME_SETTING_KEY = "Volume";
  const char* const ON_VIDEO_COMPLETE_SETTING_KEY = "OnVideoComplete";

  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void play(const std::string& videoPath, sol::table videoSettings)
    {
      Celeste::Media::Video::play(videoPath, createVideoSettings(videoSettings));
    }

    //------------------------------------------------------------------------------------------------
    void playAsync(const std::string& videoPath, sol::table videoSettings)
    {
      Celeste::Media::Video::playAsync(videoPath, createVideoSettings(videoSettings));
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    sol::table videoTable = LuaState::instance().create_named_table("Video");
    videoTable.set_function("play", &Internals::play);
    videoTable.set_function("playAsync", &Internals::playAsync);
  }

  //------------------------------------------------------------------------------------------------
  Celeste::Media::VideoSettings createVideoSettings(sol::table videoSettings)
  {
    Celeste::Media::VideoSettings settings;
    settings.m_autoExit = videoSettings.get_or<bool>(AUTO_EXIT_SETTING_KEY, settings.m_autoExit);
    settings.m_volume = videoSettings.get_or<float>(VOLUME_SETTING_KEY, settings.m_volume);

    sol::function callback = videoSettings.get_or<sol::function>(ON_VIDEO_COMPLETE_SETTING_KEY, sol::nil);
    if (callback.valid() && callback != sol::nil)
    {
      settings.m_videoCompleteCallback = callback;
    }

    return settings;
  }
}