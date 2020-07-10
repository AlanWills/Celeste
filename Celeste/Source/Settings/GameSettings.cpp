#include "Settings/GameSettings.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Audio/AudioManager.h"
#include "Scene/SceneUtils.h"
#include "Viewport/OpenGLWindow.h"
#include "Serialization/MathsSerializers.h"

using namespace Celeste::XML;


namespace Celeste::Settings
{
  REGISTER_SCRIPTABLE_OBJECT(GameSettings)

    //------------------------------------------------------------------------------------------------
    const Path GameSettings::SETTINGS_RELATIVE_PATH = Path("Data", "AppData", "GameSettings.asset");

  //------------------------------------------------------------------------------------------------
  GameSettings::GameSettings() :
    Inherited(),
    m_windowTitle(createReferenceField<std::string>("window_title")),
    m_windowIcon(createReferenceField<std::string>("window_icon")),
    m_resolution(createReferenceField<glm::vec2>("resolution")),
    m_windowed(createValueField<bool>("windowed")),
    m_vsyncEnabled(createValueField("vsync_enabled", true)),
    m_masterVolume(createValueField("master_volume", 1.0f)),
    m_musicVolume(createValueField("music_volume", 1.0f)),
    m_sfxVolume(createValueField("sfx_volume", 1.0f))
  {
  }

  //------------------------------------------------------------------------------------------------
  void GameSettings::apply() const
  {
    OpenGLWindow& window = getWindow();
    window.setTitle(getWindowTitle());
    window.setIcon(Path(Resources::getResourcesDirectory(), getWindowIcon()).as_string());
    window.setWindowMode(isWindowed() ? OpenGLWindow::WindowMode::kWindowed : OpenGLWindow::WindowMode::kFullScreen);

    // Set window dimensions after we set window mode because the order matters
    const glm::vec2& resolution = getResolution();
    if (resolution != glm::zero<glm::vec2>())
    {
      window.setResolution(resolution);
    }

    // Vsync
    glfwSwapInterval(isVsyncEnabled() ? 1 : 0);

    Audio::AudioManager& audioManager = Audio::getAudioManager();

    audioManager.setMasterVolume(getMasterVolume());
    audioManager.setMusicVolume(getMusicVolume());
    audioManager.setSFXVolume(getSFXVolume());
  }
}