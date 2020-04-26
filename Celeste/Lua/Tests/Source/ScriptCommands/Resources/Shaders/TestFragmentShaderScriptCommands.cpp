#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "ScriptCommands/Resources/Shaders/FragmentShaderScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Mocks/Resources/Shaders/MockFragmentShader.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;
using namespace Celeste::Resources;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestFragmentShaderScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_Initialize_Adds_FragmentShaderUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["FragmentShader"].valid());

    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["FragmentShader"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_Initialize_Adds_as_ToFragmentShaderTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["FragmentShader"]["as"].valid());

    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["FragmentShader"]["as"].valid());
  }

#pragma endregion

#pragma region FragmentShader As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_FragmentShader_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["FragmentShader"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_FragmentShader_as_InputtingNull_CastingToFragmentShaderType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize(state);

    auto functionResult = state.globals()["FragmentShader"]["as"].get<sol::protected_function>().call(nullptr, "FragmentShader");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_FragmentShader_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize(state);

    class MockFragmentShader : public Celeste::Resources::FragmentShader {};
    state.new_usertype<MockFragmentShader>("MockFragmentShader");

    auto functionResult = state.globals()["FragmentShader"]["as"].get<sol::protected_function>().call(nullptr, "MockFragmentShader");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_FragmentShader_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["FragmentShader"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_FragmentShaderHandle_as_InputtingNullFragmentShaderHandle_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["FragmentShader"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_FragmentShader_as_InputtingNonNullFragmentShader_CastingToBaseType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    FragmentShader fragmentShader;
    auto functionResult = state.globals()["FragmentShader"]["as"].get<sol::protected_function>().call(&fragmentShader, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&fragmentShader == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_FragmentShader_as_InputtingNonNullFragmentShader_CastingToFragmentShaderType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize(state);

    FragmentShader fragmentShader;
    auto functionResult = state.globals()["FragmentShader"]["as"].get<sol::protected_function>().call(&fragmentShader, "FragmentShader");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&fragmentShader == functionResult.get<FragmentShader*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_FragmentShader_as_InputtingNonNullFragmentShader_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize(state);

    class MockFragmentShader : public Celeste::Resources::FragmentShader {};
    state.new_usertype<MockFragmentShader>("MockFragmentShader");

    FragmentShader fragmentShader;
    auto functionResult = state.globals()["FragmentShader"]["as"].get<sol::protected_function>().call(&fragmentShader, "MockFragmentShader");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_FragmentShader_as_InputtingNonNullFragmentShader_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    FragmentShader fragmentShader;
    auto functionResult = state.globals()["FragmentShader"]["as"].get<sol::protected_function>().call(&fragmentShader, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_FragmentShader_as_InputtingNonNullFragmentShader_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["FragmentShader"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}