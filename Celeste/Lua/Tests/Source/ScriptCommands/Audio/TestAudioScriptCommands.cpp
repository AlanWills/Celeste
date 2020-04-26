#include "ScriptCommands/Audio/AudioScriptCommands.h"
#include "ScriptCommands/Objects/ComponentScriptCommands.h"
#include "Lua/LuaState.h"

#include "Audio/AudioUtils.h"
#include "Audio/AudioManager.h"

#include "UtilityHeaders/UnitTestHeaders.h"
#include "Objects/Component.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestAudioScriptCommands)

  //------------------------------------------------------------------------------------------------
  void TestAudioScriptCommands::testInitialize()
  {
    Celeste::Lua::ComponentScriptCommands::initialize(Celeste::Lua::LuaState::instance());
  }

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_Initialize_Adds_AudioTable_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Audio::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals().get_or<sol::table>("Audio", sol::nil).valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_Initialize_Adds_getMasterVolume_ScriptCommand_ToAudioTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Audio::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Audio"]["getMasterVolume"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_Initialize_Adds_setMasterVolume_ScriptCommand_ToAudioTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Audio::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Audio"]["setMasterVolume"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_Initialize_Adds_getMusicVolume_ScriptCommand_ToAudioTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Audio::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Audio"]["getMusicVolume"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_Initialize_Adds_setMusicVolume_ScriptCommand_ToAudioTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Audio::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Audio"]["setMusicVolume"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_Initialize_Adds_getSFXVolume_ScriptCommand_ToAudioTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Audio::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Audio"]["getSFXVolume"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_Initialize_Adds_setSFXVolume_ScriptCommand_ToAudioTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Audio::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Audio"]["setSFXVolume"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_Initialize_InitializesAudioSourceScriptCommands)
  {
    sol::state& state = LuaState::instance();
    
    Assert::IsFalse(state.globals()["Audio"]["AudioSource"].valid());

    Celeste::Lua::Audio::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["AudioSource"].valid());
  }

#pragma endregion

#pragma region Get Master Volume Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_GetMasterVolume_ReturnsAudioManagerMasterVolume)
  {
    Audio::getAudioManager().setMasterVolume(0.5f);

    Assert::AreEqual(0.5f, Celeste::Lua::Audio::ScriptCommands::getMasterVolume());

    Audio::getAudioManager().setMasterVolume(1);

    Assert::AreEqual(1.0f, Celeste::Lua::Audio::ScriptCommands::getMasterVolume());
  }

#pragma region

#pragma region Set Master Volume Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_SetMasterVolume_SetsAudioManagerMasterVolume)
  {
    Celeste::Lua::Audio::ScriptCommands::setMasterVolume(0.5f);

    Assert::AreEqual(0.5f, Audio::getAudioManager().getMasterVolume());

    Celeste::Lua::Audio::ScriptCommands::setMasterVolume(1.0f);

    Assert::AreEqual(1.0f, Audio::getAudioManager().getMasterVolume());
  }

#pragma region

#pragma region Get Music Volume Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_GetMusicVolume_ReturnsAudioManagerMusicVolume)
  {
    Audio::getAudioManager().setMusicVolume(0.5f);

    Assert::AreEqual(0.5f, Celeste::Lua::Audio::ScriptCommands::getMusicVolume());

    Audio::getAudioManager().setMusicVolume(1);

    Assert::AreEqual(1.0f, Celeste::Lua::Audio::ScriptCommands::getMusicVolume());
  }

#pragma region

#pragma region Set Music Volume Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_SetMusicVolume_SetsAudioManagerMusicVolume)
  {
    Celeste::Lua::Audio::ScriptCommands::setMusicVolume(0.5f);

    Assert::AreEqual(0.5f, Audio::getAudioManager().getMusicVolume());

    Celeste::Lua::Audio::ScriptCommands::setMusicVolume(1.0f);

    Assert::AreEqual(1.0f, Audio::getAudioManager().getMusicVolume());
  }

#pragma region

#pragma region Get SFX Volume Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_GetSFXVolume_ReturnsAudioManagerSFXVolume)
  {
    Audio::getAudioManager().setSFXVolume(0.5f);

    Assert::AreEqual(0.5f, Celeste::Lua::Audio::ScriptCommands::getSFXVolume());

    Audio::getAudioManager().setSFXVolume(1);

    Assert::AreEqual(1.0f, Celeste::Lua::Audio::ScriptCommands::getSFXVolume());
  }

#pragma region

#pragma region Set SFX Volume Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioScriptCommands_SetSFXVolume_SetsAudioManagerSFXVolume)
  {
    Celeste::Lua::Audio::ScriptCommands::setSFXVolume(0.5f);

    Assert::AreEqual(0.5f, Audio::getAudioManager().getSFXVolume());

    Celeste::Lua::Audio::ScriptCommands::setSFXVolume(1.0f);

    Assert::AreEqual(1.0f, Audio::getAudioManager().getSFXVolume());
  }

#pragma region

  };
}