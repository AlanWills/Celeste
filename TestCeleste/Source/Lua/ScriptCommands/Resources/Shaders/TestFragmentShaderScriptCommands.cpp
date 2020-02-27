#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "Lua/ScriptCommands/Resources/Shaders/FragmentShaderScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Mocks/Resources/Shaders/MockFragmentShader.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;
using namespace Celeste::Resources;


namespace TestCeleste::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestFragmentShaderScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_Initialize_Adds_FragmentShaderUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["FragmentShader"].valid());

    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize();

    Assert::IsTrue(state.globals()["FragmentShader"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_Initialize_Adds_as_ToFragmentShaderTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["FragmentShader"]["as"].valid());

    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize();

    Assert::IsTrue(state.globals()["FragmentShader"]["as"].valid());
  }

#pragma endregion

#pragma region FragmentShader As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_FragmentShader_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["FragmentShader"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_FragmentShader_as_InputtingNull_CastingToFragmentShaderType_ReturnsNil)
  {
    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    auto functionResult = state.globals()["FragmentShader"]["as"].get<sol::protected_function>().call(nullptr, "FragmentShader");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_FragmentShader_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockFragmentShader : public Celeste::Resources::FragmentShader {};
    state.new_usertype<MockFragmentShader>("MockFragmentShader");

    auto functionResult = state.globals()["FragmentShader"]["as"].get<sol::protected_function>().call(nullptr, "MockFragmentShader");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_FragmentShader_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["FragmentShader"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_FragmentShaderHandle_as_InputtingNullFragmentShaderHandle_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["FragmentShader"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_FragmentShader_as_InputtingNonNullFragmentShader_CastingToBaseType_ReturnsCorrectPtr)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    FragmentShader fragmentShader;
    auto functionResult = state.globals()["FragmentShader"]["as"].get<sol::protected_function>().call(&fragmentShader, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&fragmentShader == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_FragmentShader_as_InputtingNonNullFragmentShader_CastingToFragmentShaderType_ReturnsCorrectPtr)
  {
    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    FragmentShader fragmentShader;
    auto functionResult = state.globals()["FragmentShader"]["as"].get<sol::protected_function>().call(&fragmentShader, "FragmentShader");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&fragmentShader == functionResult.get<FragmentShader*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_FragmentShader_as_InputtingNonNullFragmentShader_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize();

    sol::state& state = LuaState::instance();

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
    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    FragmentShader fragmentShader;
    auto functionResult = state.globals()["FragmentShader"]["as"].get<sol::protected_function>().call(&fragmentShader, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FragmentShaderScriptCommands_FragmentShader_as_InputtingNonNullFragmentShader_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::Resources::FragmentShaderScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["FragmentShader"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}