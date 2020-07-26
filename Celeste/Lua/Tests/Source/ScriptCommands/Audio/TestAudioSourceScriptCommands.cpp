#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "ScriptCommands/Audio/AudioSourceScriptCommands.h"
#include "ScriptCommands/Utils/ScriptCommandUtils.h"
#include "Lua/LuaState.h"
#include "Resources/ResourceManager.h"
#include "CelesteTestUtils/Assert/AssertCel.h"
#include "TestResources/TestResources.h"

#include "Mocks/Audio/MockAudioSource.h"

using LuaState = Celeste::Lua::LuaState;
using AudioSource = Celeste::Audio::AudioSource;

using namespace Celeste;
using namespace Celeste::Audio;
using namespace Celeste::Resources;


namespace TestCeleste::Lua::Audio::AudioSourceScriptCommands
{
  CELESTE_TEST_CLASS(TestAudioSourceScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_Initialize_Adds_AudioSourceUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["AudioSource"].valid());

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["AudioSource"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_Initialize_Adds_getSound_ToAudioSourceTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["AudioSource"]["getSound"].valid());

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["AudioSource"]["getSound"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_Initialize_Adds_setSound_ToAudioSourceTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["AudioSource"]["setSound"].valid());

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["AudioSource"]["setSound"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_Initialize_Adds_getAudioType_ToAudioSourceTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["AudioSource"]["getAudioType"].valid());

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["AudioSource"]["getAudioType"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_Initialize_Adds_setAudioType_ToAudioSourceTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["AudioSource"]["setAudioType"].valid());

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["AudioSource"]["setAudioType"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_Initialize_Adds_getVolume_ToAudioSourceTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["AudioSource"]["getVolume"].valid());

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["AudioSource"]["getVolume"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_Initialize_Adds_setVolume_ToAudioSourceTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["AudioSource"]["setVolume"].valid());

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["AudioSource"]["setVolume"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_Initialize_Adds_isLooping_ToAudioSourceTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["AudioSource"]["isLooping"].valid());

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["AudioSource"]["isLooping"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_Initialize_Adds_setLooping_ToAudioSourceTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["AudioSource"]["setLooping"].valid());

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["AudioSource"]["setLooping"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_Initialize_Adds_isPlaying_ToAudioSourceTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["AudioSource"]["isPlaying"].valid());

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["AudioSource"]["isPlaying"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_Initialize_Adds_play_ToAudioSourceTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["AudioSource"]["play"].valid());

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["AudioSource"]["play"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_Initialize_Adds_stop_ToAudioSourceTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["AudioSource"]["stop"].valid());

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["AudioSource"]["stop"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_Initialize_Adds_as_ToAudioSourceTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["AudioSource"]["as"].valid());

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["AudioSource"]["as"].valid());
  }

#pragma endregion

#pragma region Get Audio Type Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_getAudioType_AudioTypeIs_kMusic_ReturnsMusic)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    GameObject gameObject;
    AudioSource audioSource(gameObject);
    audioSource.setAudioType(AudioType::kMusic);

    Assert::IsTrue(AudioType::kMusic == audioSource.getAudioType());

    auto functionResult = state.globals()["AudioSource"]["getAudioType"].get<sol::protected_function>().call(audioSource);

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual("Music", functionResult.get<std::string>().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_getAudioType_AudioTypeIs_kSFX_ReturnsSFX)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    GameObject gameObject;
    AudioSource audioSource(gameObject);
    audioSource.setAudioType(AudioType::kSFX);

    Assert::IsTrue(AudioType::kSFX == audioSource.getAudioType());

    auto functionResult = state.globals()["AudioSource"]["getAudioType"].get<sol::protected_function>().call(audioSource);

    Assert::IsTrue(functionResult.valid());
    Assert::AreEqual("SFX", functionResult.get<std::string>().c_str());
  }

#pragma endregion

#pragma region Set Sound Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_SetSound_InputtingNullptr_SetsSoundToNullptr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    GameObject gameObject;
    AudioSource audioSource(gameObject);

    auto sound = getResourceManager().load<Sound>(TestResources::getButtonHoverWavRelativePath());
    audioSource.setSound(sound);

    Assert::IsNotNull(audioSource.getSound());

    Sound* soundNullptr = nullptr;
    auto functionResult = state.globals()["AudioSource"]["setSound"].get<sol::protected_function>().call(audioSource, soundNullptr);

    Assert::IsTrue(functionResult.valid());
    Assert::IsNull(audioSource.getSound());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_SetSound_InputtingNonNullptr_SetsSoundToCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    GameObject gameObject;
    AudioSource audioSource(gameObject);

    auto sound = getResourceManager().load<Sound>(TestResources::getButtonHoverWavRelativePath());
    audioSource.setSound(nullptr);

    Assert::IsNull(audioSource.getSound());

    auto functionResult = state.globals()["AudioSource"]["setSound"].get<sol::protected_function>().call(audioSource, sound);

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sound == audioSource.getSound());
  }

#pragma endregion

#pragma region AudioSource As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_AudioSource_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["AudioSource"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_AudioSource_as_InputtingNull_CastingToAudioSourceType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    auto functionResult = state.globals()["AudioSource"]["as"].get<sol::protected_function>().call(nullptr, "AudioSource");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_AudioSource_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    class MockAudioSource : public Celeste::Audio::AudioSource {};
    state.new_usertype<MockAudioSource>("MockAudioSource");

    auto functionResult = state.globals()["AudioSource"]["as"].get<sol::protected_function>().call(nullptr, "MockAudioSource");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_AudioSource_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["AudioSource"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_AudioSourceHandle_as_InputtingNullAudioSourceHandle_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["AudioSource"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_AudioSource_as_InputtingNonNullAudioSource_CastingToBaseType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    GameObject gameObject;
    AudioSource audioSource(gameObject);
    auto functionResult = state.globals()["AudioSource"]["as"].get<sol::protected_function>().call(&audioSource, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&audioSource == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_AudioSource_as_InputtingNonNullAudioSource_CastingToAudioSourceType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    GameObject gameObject;
    AudioSource audioSource(gameObject);
    auto functionResult = state.globals()["AudioSource"]["as"].get<sol::protected_function>().call(&audioSource, "AudioSource");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&audioSource == functionResult.get<AudioSource*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_AudioSource_as_InputtingNonNullAudioSource_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    class MockAudioSource : public Celeste::Audio::AudioSource {};
    state.new_usertype<MockAudioSource>("MockAudioSource");

    GameObject gameObject;
    AudioSource audioSource(gameObject);
    auto functionResult = state.globals()["AudioSource"]["as"].get<sol::protected_function>().call(&audioSource, "MockAudioSource");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_AudioSource_as_InputtingNonNullAudioSource_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    GameObject gameObject;
    AudioSource audioSource(gameObject);
    auto functionResult = state.globals()["AudioSource"]["as"].get<sol::protected_function>().call(&audioSource, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AudioSourceScriptCommands_AudioSource_as_InputtingNonNullAudioSource_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Audio::AudioSourceScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["AudioSource"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}