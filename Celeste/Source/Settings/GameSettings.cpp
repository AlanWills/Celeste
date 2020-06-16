#include "Settings/GameSettings.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Audio/AudioManager.h"
#include "OpenGL/GL.h"

using namespace Celeste::XML;


namespace Celeste::Settings
{
  REGISTER_SCRIPTABLE_OBJECT(GameSettings)

  //------------------------------------------------------------------------------------------------
  GameSettings::GameSettings() :
    Inherited(),
    m_masterVolume(createValueField("master_volume", 1.0f)),
    m_musicVolume(createValueField("music_volume", 1.0f)),
    m_sfxVolume(createValueField("sfx_volume", 1.0f)),
    m_vsyncEnabled(createValueField("vsync_enabled", true))
  {
  }

  //------------------------------------------------------------------------------------------------
  void GameSettings::apply() const
  {
    Audio::AudioManager& audioManager = Audio::getAudioManager();

    audioManager.setMasterVolume(getMasterVolume());
    audioManager.setMusicVolume(getMusicVolume());
    audioManager.setSFXVolume(getSFXVolume());

    glfwSwapInterval(isVsyncEnabled() ? 1 : 0);
  }
}