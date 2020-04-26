#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Settings/GameSettingsScriptCommands.h"
#include "Lua/LuaState.h"

#include "Settings/GameSettings.h"
#include "TestResources/Settings/GameSettingsLoadingResources.h"
#include "Audio/AudioManager.h"
#include "AssertExt.h"
#include "FileAssert.h"

using LuaState = Celeste::Lua::LuaState;
using GameSettings = Settings::GameSettings;


namespace TestCelesteLua::Lua::GameSettingsScriptCommands
{
  CELESTE_TEST_CLASS(TestGameSettingsScriptCommands)

  float originalMasterVolume;
  float originalMusicVolume;
  float originalSFXVolume;

  //------------------------------------------------------------------------------------------------
  void TestGameSettingsScriptCommands::testInitialize()
  {
    Celeste::Audio::AudioManager& audioSourceManager = Celeste::Audio::getAudioManager();

    originalMasterVolume = audioSourceManager.getMasterVolume();
    originalMusicVolume = audioSourceManager.getMusicVolume();
    originalSFXVolume = audioSourceManager.getSFXVolume();
  }

  //------------------------------------------------------------------------------------------------
  void TestGameSettingsScriptCommands::testCleanup()
  {
    Celeste::Audio::AudioManager& audioSourceManager = Celeste::Audio::getAudioManager();

    audioSourceManager.setMasterVolume(originalMasterVolume);
    audioSourceManager.setMusicVolume(originalMusicVolume);
    audioSourceManager.setSFXVolume(originalSFXVolume);
  }

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Initialize_Adds_GameSettingsUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[GameSettings::type_name()].valid());

    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    Assert::IsTrue(state[GameSettings::type_name()].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Initialize_Adds_create_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[GameSettings::type_name()]["create"].valid());

    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    Assert::IsTrue(state[GameSettings::type_name()]["create"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Initialize_Adds_load_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[GameSettings::type_name()]["load"].valid());

    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    Assert::IsTrue(state[GameSettings::type_name()]["load"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Initialize_Adds_save_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[GameSettings::type_name()]["save"].valid());

    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    Assert::IsTrue(state[GameSettings::type_name()]["save"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Initialize_Adds_apply_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[GameSettings::type_name()]["apply"].valid());

    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    Assert::IsTrue(state[GameSettings::type_name()]["apply"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Initialize_Adds_getMasterVolume_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[GameSettings::type_name()]["getMasterVolume"].valid());

    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    Assert::IsTrue(state[GameSettings::type_name()]["getMasterVolume"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Initialize_Adds_setMasterVolume_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[GameSettings::type_name()]["setMasterVolume"].valid());

    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    Assert::IsTrue(state[GameSettings::type_name()]["setMasterVolume"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Initialize_Adds_getMusicVolume_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[GameSettings::type_name()]["getMusicVolume"].valid());

    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    Assert::IsTrue(state[GameSettings::type_name()]["getMusicVolume"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Initialize_Adds_setMusicVolume_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[GameSettings::type_name()]["setMusicVolume"].valid());

    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    Assert::IsTrue(state[GameSettings::type_name()]["setMusicVolume"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Initialize_Adds_getSFXVolume_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[GameSettings::type_name()]["getSFXVolume"].valid());

    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    Assert::IsTrue(state[GameSettings::type_name()]["getSFXVolume"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Initialize_Adds_setSFXVolume_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[GameSettings::type_name()]["setSFXVolume"].valid());

    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    Assert::IsTrue(state[GameSettings::type_name()]["setSFXVolume"].valid());
  }

#pragma endregion

#pragma region Create Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Create_ReturnsNewInstanceOfGameSettings)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    Assert::IsTrue(state.script(R"(
            gameSettings = GameSettings.create("Test")
            )").valid());

    Assert::IsTrue(state.globals()["gameSettings"].valid());
    Assert::IsNotNull(state.globals()["gameSettings"].get<Settings::GameSettings*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Create_SetsNameToInput)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    Assert::IsTrue(state.script(R"(
            gameSettings = GameSettings.create("Test")
            )").valid());

    Assert::AreEqual("Test", state.globals()["gameSettings"].get<Settings::GameSettings*>()->getName().c_str());
  }

#pragma endregion

#pragma region Load Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Load_InputtingNonExistentPath_ReturnsNullptr)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    Assert::IsTrue(state.script(R"(
            gameSettings = GameSettings.load("WubbaLubbaDubDub")
            )").valid());

    Assert::IsFalse(state.globals()["gameSettings"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Load_InputtingExistentPath_ToInvalidFile_ReturnsNullptr)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    Assert::IsTrue(state.script("gameSettings = GameSettings.load([[" + GameSettingsLoadingResources::getInvalidFullPath().as_string() + "]])").valid());
    Assert::IsFalse(state.globals()["gameSettings"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Load_InputtingExistentPath_ToValidFile_ReturnsGameSettingsInstance)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    Assert::IsTrue(state.script("gameSettings = GameSettings.load([[" + GameSettingsLoadingResources::getValidFullPath().as_string() + "]])").valid());
    Assert::IsTrue(state.globals()["gameSettings"].valid());
    Assert::IsNotNull(state.globals()["gameSettings"].get<Settings::GameSettings*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Load_InputtingExistentPath_ToValidFile_SetsValuesOfCreatedInstanceCorrectly)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    Assert::IsTrue(state.script("gameSettings = GameSettings.load([[" + GameSettingsLoadingResources::getValidFullPath().as_string() + "]])").valid());

    auto gameSettings = state.globals()["gameSettings"].get<Settings::GameSettings*>();

    Assert::AreEqual("Valid", gameSettings->getName().c_str());
    Assert::AreEqual("34b0d489-8485-4391-b3b9-b3f062e90c4a", gameSettings->getGuid().str().c_str());
    Assert::AreEqual(0.6f, gameSettings->getMasterVolume());
    Assert::AreEqual(0.5f, gameSettings->getMusicVolume());
    Assert::AreEqual(0.4f, gameSettings->getSFXVolume());
  }

#pragma endregion

#pragma region Load Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_save_InputtingInvalidPath_DoesNotSaveScriptableObject)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    std::unique_ptr<GameSettings> gameSettings = ScriptableObject::create<GameSettings>("Test");
    std::string filePath = "";

    FileAssert::FileDoesNotExist(filePath);

    auto result = state[GameSettings::type_name()]["save"].get<sol::protected_function>().call(*gameSettings, filePath);

    Assert::IsTrue(result.valid());
    FileAssert::FileDoesNotExist(filePath);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_save_InputtingValidFullPath_FileDoesNotExist_CreatesFile)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    std::unique_ptr<GameSettings> gameSettings = ScriptableObject::create<GameSettings>("Test");
    std::string filePath = Path(TempDirectory::getFullPath(), "SO.asset").as_string();

    FileAssert::FileDoesNotExist(filePath);

    auto result = state[GameSettings::type_name()]["save"].get<sol::protected_function>().call(*gameSettings, filePath);

    Assert::IsTrue(result.valid());
    FileAssert::FileExists(filePath);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_save_InputtingValidFullPath_FileExists_OverwritesFile)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    std::unique_ptr<GameSettings> gameSettings = ScriptableObject::create<GameSettings>("Test");
    std::string filePath = Path(TempDirectory::getFullPath(), "SO.asset").as_string();
    
    File file(filePath);
    file.create();
    file.append("Test");

    FileAssert::FileExists(filePath);
    FileAssert::FileContentsEqual(filePath, "Test");

    auto result = state[GameSettings::type_name()]["save"].get<sol::protected_function>().call(*gameSettings, filePath);

    Assert::IsTrue(result.valid());
    FileAssert::FileContentsNotEqual(filePath, "Test");
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_save_InputtingValidRelativePath_FileDoesNotExist_CreatesFile)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    std::unique_ptr<GameSettings> gameSettings = ScriptableObject::create<GameSettings>("Test");
    std::string relativeFilePath = Path(TempDirectory::getRelativePath(), "SO.asset").as_string();
    std::string fullFilePath = Path(TempDirectory::getFullPath(), "SO.asset").as_string();

    FileAssert::FileDoesNotExist(fullFilePath);

    auto result = state[GameSettings::type_name()]["save"].get<sol::protected_function>().call(*gameSettings, relativeFilePath);

    Assert::IsTrue(result.valid());
    FileAssert::FileExists(fullFilePath);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_save_InputtingValidRelativePath_FileExists_OverwritesFile)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    std::unique_ptr<GameSettings> gameSettings = ScriptableObject::create<GameSettings>("Test");
    std::string relativeFilePath = Path(TempDirectory::getRelativePath(), "SO.asset").as_string();
    std::string fullFilePath = Path(TempDirectory::getFullPath(), "SO.asset").as_string();

    File file(fullFilePath);
    file.create();
    file.append("Test");

    FileAssert::FileExists(fullFilePath);
    FileAssert::FileContentsEqual(fullFilePath, "Test");

    auto result = state[GameSettings::type_name()]["save"].get<sol::protected_function>().call(*gameSettings, relativeFilePath);

    Assert::IsTrue(result.valid());
    FileAssert::FileContentsNotEqual(fullFilePath, "Test");
  }

#pragma endregion

#pragma region Get Apply Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Apply_InputtingNonExistentRelativePath_DoesNothing)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);
    Audio::AudioManager& audioSourceManager = Audio::getAudioManager();

    Assert::AreEqual(originalMasterVolume, audioSourceManager.getMasterVolume());
    Assert::AreEqual(originalMusicVolume, audioSourceManager.getMusicVolume());
    Assert::AreEqual(originalSFXVolume, audioSourceManager.getSFXVolume());

    auto result = state["GameSettings"]["apply"]("WubbaLubbaDubDub.asset");

    Assert::IsTrue(result.valid());
    Assert::AreEqual(originalMasterVolume, audioSourceManager.getMasterVolume());
    Assert::AreEqual(originalMusicVolume, audioSourceManager.getMusicVolume());
    Assert::AreEqual(originalSFXVolume, audioSourceManager.getSFXVolume());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Apply_InputtingNonExistentFullPath_DoesNothing)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);
    Audio::AudioManager& audioSourceManager = Audio::getAudioManager();

    Assert::AreEqual(originalMasterVolume, audioSourceManager.getMasterVolume());
    Assert::AreEqual(originalMusicVolume, audioSourceManager.getMusicVolume());
    Assert::AreEqual(originalSFXVolume, audioSourceManager.getSFXVolume());

    auto result = state["GameSettings"]["apply"](Path(TestResources::getResourcesDirectory(), "WubbaLubbaDubDub.asset").as_string());

    Assert::IsTrue(result.valid());
    Assert::AreEqual(originalMasterVolume, audioSourceManager.getMasterVolume());
    Assert::AreEqual(originalMusicVolume, audioSourceManager.getMusicVolume());
    Assert::AreEqual(originalSFXVolume, audioSourceManager.getSFXVolume());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Apply_InputtingExistentRelativePath_InvalidGameSettings_DoesNothing)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);
    Audio::AudioManager& audioSourceManager = Audio::getAudioManager();

    FileAssert::FileExists(Path(TestResources::getResourcesDirectory(), GameSettingsLoadingResources::getInvalidRelativePath()).as_string());
    Assert::AreEqual(originalMasterVolume, audioSourceManager.getMasterVolume());
    Assert::AreEqual(originalMusicVolume, audioSourceManager.getMusicVolume());
    Assert::AreEqual(originalSFXVolume, audioSourceManager.getSFXVolume());

    auto result = state["GameSettings"]["apply"](GameSettingsLoadingResources::getInvalidRelativePath());

    Assert::IsTrue(result.valid());
    Assert::AreEqual(originalMasterVolume, audioSourceManager.getMasterVolume());
    Assert::AreEqual(originalMusicVolume, audioSourceManager.getMusicVolume());
    Assert::AreEqual(originalSFXVolume, audioSourceManager.getSFXVolume());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Apply_InputtingExistentFullPath_InvalidGameSettings_DoesNothing)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);
    Audio::AudioManager& audioSourceManager = Audio::getAudioManager();

    FileAssert::FileExists(GameSettingsLoadingResources::getInvalidFullPath().as_string());
    Assert::AreEqual(originalMasterVolume, audioSourceManager.getMasterVolume());
    Assert::AreEqual(originalMusicVolume, audioSourceManager.getMusicVolume());
    Assert::AreEqual(originalSFXVolume, audioSourceManager.getSFXVolume());

    auto result = state["GameSettings"]["apply"](GameSettingsLoadingResources::getInvalidFullPath().as_string());

    Assert::IsTrue(result.valid());
    Assert::AreEqual(originalMasterVolume, audioSourceManager.getMasterVolume());
    Assert::AreEqual(originalMusicVolume, audioSourceManager.getMusicVolume());
    Assert::AreEqual(originalSFXVolume, audioSourceManager.getSFXVolume());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Apply_InputtingExistentRelativePath_ValidGameSettings_AppliesSettingsCorrectly)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);
    Audio::AudioManager& audioSourceManager = Audio::getAudioManager();

    FileAssert::FileExists(Path(TestResources::getResourcesDirectory(), GameSettingsLoadingResources::getValidRelativePath()).as_string());
    Assert::AreEqual(originalMasterVolume, audioSourceManager.getMasterVolume());
    Assert::AreEqual(originalMusicVolume, audioSourceManager.getMusicVolume());
    Assert::AreEqual(originalSFXVolume, audioSourceManager.getSFXVolume());

    auto result = state["GameSettings"]["apply"](GameSettingsLoadingResources::getValidRelativePath());

    Assert::IsTrue(result.valid());
    Assert::AreEqual(0.6f, audioSourceManager.getMasterVolume());
    Assert::AreEqual(0.5f, audioSourceManager.getMusicVolume());
    Assert::AreEqual(0.4f, audioSourceManager.getSFXVolume());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_Apply_InputtingExistentFullPath_ValidGameSettings_AppliesSettingsCorrectly)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);
    Audio::AudioManager& audioSourceManager = Audio::getAudioManager();

    FileAssert::FileExists(GameSettingsLoadingResources::getValidFullPath().as_string());
    Assert::AreEqual(originalMasterVolume, audioSourceManager.getMasterVolume());
    Assert::AreEqual(originalMusicVolume, audioSourceManager.getMusicVolume());
    Assert::AreEqual(originalSFXVolume, audioSourceManager.getSFXVolume());

    auto result = state["GameSettings"]["apply"](GameSettingsLoadingResources::getValidFullPath().as_string());

    Assert::IsTrue(result.valid());
    Assert::AreEqual(0.6f, audioSourceManager.getMasterVolume());
    Assert::AreEqual(0.5f, audioSourceManager.getMusicVolume());
    Assert::AreEqual(0.4f, audioSourceManager.getSFXVolume());
  }

#pragma endregion

#pragma region Get Master Volume Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_GetMasterVolume_ReturnsCorrectValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    Assert::IsTrue(state.script("gameSettings = GameSettings.load([[" + GameSettingsLoadingResources::getValidFullPath().as_string() + "]]):getMasterVolume()").valid());
    Assert::IsTrue(state.globals()["gameSettings"].valid());
    Assert::AreEqual(0.6f, state.globals()["gameSettings"].get<float>());
  }

#pragma endregion

#pragma region Set Master Volume Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_SetMasterVolume_ReturnsCorrectValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    std::unique_ptr<GameSettings> gameSettings = ScriptableObject::create<GameSettings>("GameSettings");
    gameSettings->setMasterVolume(0.5f);

    Assert::AreEqual(0.5f, gameSettings->getMasterVolume());

    auto result = state[GameSettings::type_name()]["setMasterVolume"].get<sol::protected_function>().call(std::reference_wrapper(gameSettings), 0.15f);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(0.15f, gameSettings->getMasterVolume());
  }

#pragma endregion

#pragma region Get Music Volume Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_GetMusicVolume_ReturnsCorrectValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    Assert::IsTrue(state.script("gameSettings = GameSettings.load([[" + GameSettingsLoadingResources::getValidFullPath().as_string() + "]]):getMusicVolume()").valid());
    Assert::IsTrue(state.globals()["gameSettings"].valid());
    Assert::AreEqual(0.5f, state.globals()["gameSettings"].get<float>());
  }

#pragma endregion

#pragma region Set Music Volume Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_SetMusicVolume_ReturnsCorrectValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    std::unique_ptr<GameSettings> gameSettings = ScriptableObject::create<GameSettings>("GameSettings");
    gameSettings->setMusicVolume(0.5f);

    Assert::AreEqual(0.5f, gameSettings->getMusicVolume());

    auto result = state[GameSettings::type_name()]["setMusicVolume"].get<sol::protected_function>().call(std::reference_wrapper(gameSettings), 0.15f);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(0.15f, gameSettings->getMusicVolume());
  }

#pragma endregion

#pragma region Get SFX Volume Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_GetSFXVolume_ReturnsCorrectValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    Assert::IsTrue(state.script("gameSettings = GameSettings.load([[" + GameSettingsLoadingResources::getValidFullPath().as_string() + "]]):getSFXVolume()").valid());
    Assert::IsTrue(state.globals()["gameSettings"].valid());
    Assert::AreEqual(0.4f, state.globals()["gameSettings"].get<float>());
  }

#pragma endregion

#pragma region Set SFX Volume Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameSettingsScriptCommands_SetSFXVolume_ReturnsCorrectValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Settings::GameSettingsScriptCommands::initialize(state);

    std::unique_ptr<GameSettings> gameSettings = ScriptableObject::create<GameSettings>("GameSettings");
    gameSettings->setSFXVolume(0.5f);

    Assert::AreEqual(0.5f, gameSettings->getSFXVolume());

    auto result = state[GameSettings::type_name()]["setSFXVolume"].get<sol::protected_function>().call(std::reference_wrapper(gameSettings), 0.15f);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(0.15f, gameSettings->getSFXVolume());
  }

#pragma endregion

  };
}