#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Settings/GameSettings.h"
#include "Resources/ResourceManager.h"
#include "Viewport/OpenGLWindow.h"
#include "Scene/SceneUtils.h"
#include "OpenGL/GL.h"
#include "Audio/AudioManager.h"
#include "XML/tinyxml2_ext.h"
#include "Serialization/MathsSerializers.h"
#include "TestResources/TestResources.h"
#include "TestResources/Settings/GameSettingsLoadingResources.h"
#include "TestUtils/Assert/FileAssert.h"

using namespace Celeste::XML;
using namespace Celeste::Settings;
using namespace Celeste::Audio;


namespace TestCeleste::Settings
{
  CELESTE_TEST_CLASS(TestGameSettings)

  glm::vec2 originalResolution;
  bool originalWindowed;

  float originalMasterVolume;
  float originalMusicVolume;
  float originalSFXVolume;

  //------------------------------------------------------------------------------------------------
  void testInitialize()
  {
    OpenGLWindow& window = getWindow();

    originalResolution = window.getResolution();
    originalWindowed = window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed;

    Audio::AudioManager& audioSourceManager = Audio::getAudioManager();

    originalMasterVolume = audioSourceManager.getMasterVolume();
    originalMusicVolume = audioSourceManager.getMusicVolume();
    originalSFXVolume = audioSourceManager.getSFXVolume();
  }

  //------------------------------------------------------------------------------------------------
  void testCleanup()
  {
    resetWindow();

    Audio::AudioManager& audioSourceManager = Audio::getAudioManager();

    audioSourceManager.setMasterVolume(originalMasterVolume);
    audioSourceManager.setMusicVolume(originalMusicVolume);
    audioSourceManager.setSFXVolume(originalSFXVolume);
  }

  //------------------------------------------------------------------------------------------------
  void resetWindow()
  {
    OpenGLWindow& window = getWindow();

    window.setResolution(originalResolution);
    window.setWindowMode(originalWindowed ? OpenGLWindow::WindowMode::kWindowed : OpenGLWindow::WindowMode::kFullScreen);
  }

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettings_Constructor_SetsResolutionToEmptyString)
  {
    std::unique_ptr<GameSettings> settings = ScriptableObject::create<GameSettings>("");

    Assert::AreEqual(glm::vec2(), settings->getResolution());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettings_Constructor_SetsWindowed_ToFalse)
  {
    std::unique_ptr<GameSettings> settings = ScriptableObject::create<GameSettings>("");

    Assert::IsFalse(settings->isWindowed());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettings_Constructor_SetsMasterVolumeToOne)
  {
    std::unique_ptr<GameSettings> settings = ScriptableObject::create<GameSettings>("");

    Assert::AreEqual(1.0f, settings->getMasterVolume());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettings_Constructor_SetsMusicVolumeToOne)
  {
    std::unique_ptr<GameSettings> settings = ScriptableObject::create<GameSettings>("");

    Assert::AreEqual(1.0f, settings->getMusicVolume());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettings_Constructor_SetsSFXVolumeToOne)
  {
    std::unique_ptr<GameSettings> settings = ScriptableObject::create<GameSettings>("");

    Assert::AreEqual(1.0f, settings->getSFXVolume());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettings_Constructor_SetsIsVsyncEnabledToTrue)
  {
    std::unique_ptr<GameSettings> settings = ScriptableObject::create<GameSettings>("");

    Assert::IsTrue(settings->isVsyncEnabled());
  }

#pragma endregion

#pragma region Load Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettings_Load_InputtingInvalidPath_ReturnsNullptr)
  {
    std::unique_ptr<GameSettings> settings(ScriptableObject::load<GameSettings>(Path("WubbaLubbaDubDub")));

    Assert::IsNull(settings.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettings_Load_InputtingPathToInvalidData_ReturnsNullptr)
  {
    Path path(GameSettingsLoadingResources::getInvalidFullPath());

    FileAssert::FileExists(path);

    std::unique_ptr<GameSettings> settings(ScriptableObject::load<GameSettings>(path));

    Assert::IsNull(settings.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettings_Load_InputtingPathToValidData_ReturnsNewGameSettingsInstance)
  {
    Path path(GameSettingsLoadingResources::getValidFullPath());

    FileAssert::FileExists(path);

    std::unique_ptr<GameSettings> settings(ScriptableObject::load<GameSettings>(path));

    Assert::IsNotNull(settings.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettings_Load_InputtingPathToValidData_SetsValuesCorrectly)
  {
    Path path(GameSettingsLoadingResources::getValidFullPath());

    FileAssert::FileExists(path);

    std::unique_ptr<GameSettings> settings(ScriptableObject::load<GameSettings>(path));

    Assert::IsNotNull(settings.get());
    Assert::AreEqual(0.6f, settings->getMasterVolume());
    Assert::AreEqual(0.5f, settings->getMusicVolume());
    Assert::AreEqual(0.4f, settings->getSFXVolume());
    Assert::IsFalse(settings->isVsyncEnabled());
  }

#pragma endregion

#pragma region Save Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettings_Save_InputtingPath_PathIsInvalid_DoesNothing)
  {
    // XML data API seems unable to NOT save a fail right now, so can't get this test working
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettings_Save_InputtingPath_FileDoesNotExist_CreatesFileWithSettingsSerializedCorrectly)
  {
    Path destPath(TempDirectory::getFullPath(), "Settings.xml");

    FileAssert::FileDoesNotExist(destPath);

    std::unique_ptr<GameSettings> settings = ScriptableObject::create<GameSettings>("");
    settings->setMasterVolume(0.5f);
    settings->setMusicVolume(0.25f);
    settings->setSFXVolume(0.1f);
    settings->setVsyncEnabled(false);
    settings->save(destPath);

    std::unique_ptr<GameSettings> settings2(ScriptableObject::load<GameSettings>(destPath));

    Assert::IsNotNull(settings2.get());
    Assert::AreEqual(0.5f, settings2->getMasterVolume());
    Assert::AreEqual(0.25f, settings2->getMusicVolume());
    Assert::AreEqual(0.1f, settings2->getSFXVolume());
    Assert::IsFalse(settings->isVsyncEnabled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettings_Save_InputtingPath_FileExists_OverwritesFileWithSettingsSerializedCorrectly)
  {
    Path destPath(TempDirectory::getFullPath(), "Settings.xml");

    FileAssert::FileDoesNotExist(destPath);

    std::unique_ptr<GameSettings> settings = ScriptableObject::create<GameSettings>("");
    settings->setMasterVolume(0.5f);
    settings->setMusicVolume(0.25f);
    settings->setSFXVolume(0.1f);
    settings->setVsyncEnabled(false);
    settings->save(destPath);

    std::unique_ptr<GameSettings> settings2(ScriptableObject::load<GameSettings>(destPath));

    Assert::IsNotNull(settings2.get());
    Assert::AreEqual(0.5f, settings2->getMasterVolume());
    Assert::AreEqual(0.25f, settings2->getMusicVolume());
    Assert::AreEqual(0.1f, settings2->getSFXVolume());
    Assert::IsFalse(settings->isVsyncEnabled());

    FileAssert::FileExists(destPath);

    settings2->setMasterVolume(0.45f);
    settings2->setMusicVolume(0.65f);
    settings2->setSFXVolume(0.0f);
    settings->setVsyncEnabled(true);
    settings2->save(destPath);

    std::unique_ptr<GameSettings> settings3(ScriptableObject::load<GameSettings>(destPath));

    Assert::AreEqual(0.45f, settings3->getMasterVolume());
    Assert::AreEqual(0.65f, settings3->getMusicVolume());
    Assert::AreEqual(0.0f, settings3->getSFXVolume());
    Assert::IsTrue(settings->isVsyncEnabled());
  }

#pragma endregion

#pragma region Apply Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettings_Apply_SetsViewportDimensionsToValue)
  {
    if (GL::isInitialized())
    {
      std::unique_ptr<GameSettings> settings = ScriptableObject::create<GameSettings>("");
      settings->setResolution(originalResolution + glm::vec2(100, 200));

      OpenGLWindow& window = getWindow();

      Assert::AreEqual(originalResolution, window.getResolution());

      settings->apply();

      Assert::AreEqual(originalResolution + glm::vec2(100, 200), window.getResolution());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettings_Apply_SetsWindowModeToValue)
  {
    if (GL::isInitialized())
    {
      std::unique_ptr<GameSettings> settings = ScriptableObject::create<GameSettings>("");
      settings->setWindowed(!originalWindowed);

      OpenGLWindow& window = getWindow();

      Assert::AreEqual(originalWindowed, window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);

      settings->apply();

      Assert::AreEqual(!originalWindowed, window.getWindowMode() == OpenGLWindow::WindowMode::kWindowed);
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettings_Apply_SetsAudioManagerMasterVolume_ToValue)
  {
    std::unique_ptr<GameSettings> settings = ScriptableObject::create<GameSettings>("");
    settings->setMasterVolume(0.5f);

    Audio::AudioManager& audioSourceManager = Audio::getAudioManager();
    audioSourceManager.setMasterVolume(0.25f);

    Assert::AreEqual(0.25f, audioSourceManager.getMasterVolume());

    settings->apply();

    Assert::AreEqual(0.5f, audioSourceManager.getMasterVolume());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettings_Apply_SetsAudioManagerMusicVolume_ToValue)
  {
    std::unique_ptr<GameSettings> settings = ScriptableObject::create<GameSettings>("");
    settings->setMusicVolume(0.5f);

    Audio::AudioManager& audioSourceManager = Audio::getAudioManager();
    audioSourceManager.setMusicVolume(0.25f);

    Assert::AreEqual(0.25f, audioSourceManager.getMusicVolume());

    settings->apply();

    Assert::AreEqual(0.5f, audioSourceManager.getMusicVolume());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettings_Apply_SetsAudioManagerSFXVolume_ToValue)
  {
    std::unique_ptr<GameSettings> settings = ScriptableObject::create<GameSettings>("");
    settings->setSFXVolume(0.5f);

    Audio::AudioManager& audioSourceManager = Audio::getAudioManager();
    audioSourceManager.setSFXVolume(0.25f);

    Assert::AreEqual(0.25f, audioSourceManager.getSFXVolume());

    settings->apply();

    Assert::AreEqual(0.5f, audioSourceManager.getSFXVolume());
  }

#pragma endregion

  };
}