#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "ScriptCommands/Resources/Audio/SoundScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Mocks/Resources/Audio/MockSound.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;

using namespace Celeste;
using namespace Celeste::Resources;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestSoundScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SoundScriptCommands_Initialize_Adds_SoundUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Sound"].valid());

    Celeste::Lua::Resources::Audio::SoundScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Sound"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SoundScriptCommands_Initialize_Adds_as_ToSoundTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Sound"]["as"].valid());

    Celeste::Lua::Resources::Audio::SoundScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Sound"]["as"].valid());
  }

#pragma endregion

#pragma region Sound As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SoundScriptCommands_Sound_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Resources::Audio::SoundScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["Sound"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SoundScriptCommands_Sound_as_InputtingNull_CastingToSoundType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::Audio::SoundScriptCommands::initialize(state);

    auto functionResult = state.globals()["Sound"]["as"].get<sol::protected_function>().call(nullptr, "Sound");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SoundScriptCommands_Sound_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::Audio::SoundScriptCommands::initialize(state);

    class MockSound : public Celeste::Resources::Sound {};
    state.new_usertype<MockSound>("MockSound");

    auto functionResult = state.globals()["Sound"]["as"].get<sol::protected_function>().call(nullptr, "MockSound");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SoundScriptCommands_Sound_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::Audio::SoundScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["Sound"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SoundScriptCommands_SoundHandle_as_InputtingNullSoundHandle_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::Audio::SoundScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Sound"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SoundScriptCommands_Sound_as_InputtingNonNullSound_CastingToBaseType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Resources::Audio::SoundScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    Sound sound;
    auto functionResult = state.globals()["Sound"]["as"].get<sol::protected_function>().call(&sound, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&sound == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SoundScriptCommands_Sound_as_InputtingNonNullSound_CastingToSoundType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::Audio::SoundScriptCommands::initialize(state);

    Sound sound;
    auto functionResult = state.globals()["Sound"]["as"].get<sol::protected_function>().call(&sound, "Sound");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&sound == functionResult.get<Sound*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SoundScriptCommands_Sound_as_InputtingNonNullSound_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::Audio::SoundScriptCommands::initialize(state);

    class MockSound : public Celeste::Resources::Sound {};
    state.new_usertype<MockSound>("MockSound");

    Sound sound;
    auto functionResult = state.globals()["Sound"]["as"].get<sol::protected_function>().call(&sound, "MockSound");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SoundScriptCommands_Sound_as_InputtingNonNullSound_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::Audio::SoundScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    Sound sound;
    auto functionResult = state.globals()["Sound"]["as"].get<sol::protected_function>().call(&sound, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SoundScriptCommands_Sound_as_InputtingNonNullSound_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::Audio::SoundScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Sound"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}