#include "Lua/ScriptCommands/Audio/AudioScriptCommands.h"
#include "Lua/ScriptCommands/Objects/ComponentScriptCommands.h"
#include "Lua/LuaState.h"

#include "Audio/AudioUtils.h"
#include "Audio/AudioManager.h"

#include "UtilityHeaders/UnitTestHeaders.h"
#include "Objects/Component.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;
using namespace Celeste::Lua::Audio;


namespace TestCeleste::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestAudioScriptCommands)

  //------------------------------------------------------------------------------------------------
  void TestAudioScriptCommands::testInitialize()
  {
    Celeste::Lua::ComponentScriptCommands::initialize();
  }

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_Initialize_Adds_AudioTable_ToGlobalTable)
  {
    AudioScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals().get_or<sol::table>("Audio", sol::nil).valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_Initialize_Adds_getMasterVolume_ScriptCommand_ToAudioTable)
  {
    AudioScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals()["Audio"]["getMasterVolume"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_Initialize_Adds_setMasterVolume_ScriptCommand_ToAudioTable)
  {
    AudioScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals()["Audio"]["setMasterVolume"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_Initialize_Adds_getMusicVolume_ScriptCommand_ToAudioTable)
  {
    AudioScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals()["Audio"]["getMusicVolume"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_Initialize_Adds_setMusicVolume_ScriptCommand_ToAudioTable)
  {
    AudioScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals()["Audio"]["setMusicVolume"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_Initialize_Adds_getSFXVolume_ScriptCommand_ToAudioTable)
  {
    AudioScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals()["Audio"]["getSFXVolume"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_Initialize_Adds_setSFXVolume_ScriptCommand_ToAudioTable)
  {
    AudioScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals()["Audio"]["setSFXVolume"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_Initialize_InitializesAudioSourceScriptCommands)
  {
    Assert::IsFalse(LuaState::instance().globals()["Audio"]["AudioSource"].valid());

    AudioScriptCommands::initialize();

    Assert::IsTrue(LuaState::instance().globals()["AudioSource"].valid());
  }

#pragma endregion

#pragma region Get Master Volume Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_GetMasterVolume_ReturnsAudioManagerMasterVolume)
  {
    Audio::getAudioManager().setMasterVolume(0.5f);

    Assert::AreEqual(0.5f, AudioScriptCommands::getMasterVolume());

    Audio::getAudioManager().setMasterVolume(1);

    Assert::AreEqual(1.0f, AudioScriptCommands::getMasterVolume());
  }

#pragma region

#pragma region Set Master Volume Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_SetMasterVolume_SetsAudioManagerMasterVolume)
  {
    AudioScriptCommands::setMasterVolume(0.5f);

    Assert::AreEqual(0.5f, Audio::getAudioManager().getMasterVolume());

    AudioScriptCommands::setMasterVolume(1.0f);

    Assert::AreEqual(1.0f, Audio::getAudioManager().getMasterVolume());
  }

#pragma region

#pragma region Get Music Volume Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_GetMusicVolume_ReturnsAudioManagerMusicVolume)
  {
    Audio::getAudioManager().setMusicVolume(0.5f);

    Assert::AreEqual(0.5f, AudioScriptCommands::getMusicVolume());

    Audio::getAudioManager().setMusicVolume(1);

    Assert::AreEqual(1.0f, AudioScriptCommands::getMusicVolume());
  }

#pragma region

#pragma region Set Music Volume Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_SetMusicVolume_SetsAudioManagerMusicVolume)
  {
    AudioScriptCommands::setMusicVolume(0.5f);

    Assert::AreEqual(0.5f, Audio::getAudioManager().getMusicVolume());

    AudioScriptCommands::setMusicVolume(1.0f);

    Assert::AreEqual(1.0f, Audio::getAudioManager().getMusicVolume());
  }

#pragma region

#pragma region Get SFX Volume Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_GetSFXVolume_ReturnsAudioManagerSFXVolume)
  {
    Audio::getAudioManager().setSFXVolume(0.5f);

    Assert::AreEqual(0.5f, AudioScriptCommands::getSFXVolume());

    Audio::getAudioManager().setSFXVolume(1);

    Assert::AreEqual(1.0f, AudioScriptCommands::getSFXVolume());
  }

#pragma region

#pragma region Set SFX Volume Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_SetSFXVolume_SetsAudioManagerSFXVolume)
  {
    AudioScriptCommands::setSFXVolume(0.5f);

    Assert::AreEqual(0.5f, Audio::getAudioManager().getSFXVolume());

    AudioScriptCommands::setSFXVolume(1.0f);

    Assert::AreEqual(1.0f, Audio::getAudioManager().getSFXVolume());
  }

#pragma region

  };
}