#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "Lua/ScriptCommands/Resources/Shaders/VertexShaderScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Mocks/Resources/Shaders/MockVertexShader.h"
#include "Utils/ObjectUtils.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;
using namespace Celeste::Resources;


namespace TestCeleste::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestVertexShaderScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VertexShaderScriptCommands_Initialize_Adds_VertexShaderUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["VertexShader"].valid());

    Celeste::Lua::Resources::VertexShaderScriptCommands::initialize();

    Assert::IsTrue(state.globals()["VertexShader"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VertexShaderScriptCommands_Initialize_Adds_as_ToVertexShaderTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["VertexShader"]["as"].valid());

    Celeste::Lua::Resources::VertexShaderScriptCommands::initialize();

    Assert::IsTrue(state.globals()["VertexShader"]["as"].valid());
  }

#pragma endregion

#pragma region VertexShader As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VertexShaderScriptCommands_VertexShader_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::Resources::VertexShaderScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["VertexShader"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VertexShaderScriptCommands_VertexShader_as_InputtingNull_CastingToVertexShaderType_ReturnsNil)
  {
    Celeste::Lua::Resources::VertexShaderScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    auto functionResult = state.globals()["VertexShader"]["as"].get<sol::protected_function>().call(nullptr, "VertexShader");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VertexShaderScriptCommands_VertexShader_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::Resources::VertexShaderScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockVertexShader : public Celeste::Resources::VertexShader {};
    state.new_usertype<MockVertexShader>("MockVertexShader");

    auto functionResult = state.globals()["VertexShader"]["as"].get<sol::protected_function>().call(nullptr, "MockVertexShader");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VertexShaderScriptCommands_VertexShader_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::Resources::VertexShaderScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["VertexShader"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VertexShaderScriptCommands_VertexShaderHandle_as_InputtingNullVertexShaderHandle_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::Resources::VertexShaderScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["VertexShader"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VertexShaderScriptCommands_VertexShader_as_InputtingNonNullVertexShader_CastingToBaseType_ReturnsCorrectPtr)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::Resources::VertexShaderScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    VertexShader vertexShader;
    auto functionResult = state.globals()["VertexShader"]["as"].get<sol::protected_function>().call(&vertexShader, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&vertexShader == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VertexShaderScriptCommands_VertexShader_as_InputtingNonNullVertexShader_CastingToVertexShaderType_ReturnsCorrectPtr)
  {
    Celeste::Lua::Resources::VertexShaderScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    VertexShader vertexShader;
    auto functionResult = state.globals()["VertexShader"]["as"].get<sol::protected_function>().call(&vertexShader, "VertexShader");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&vertexShader == functionResult.get<VertexShader*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VertexShaderScriptCommands_VertexShader_as_InputtingNonNullVertexShader_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::Resources::VertexShaderScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockVertexShader : public Celeste::Resources::VertexShader {};
    state.new_usertype<MockVertexShader>("MockVertexShader");

    VertexShader vertexShader;
    auto functionResult = state.globals()["VertexShader"]["as"].get<sol::protected_function>().call(&vertexShader, "MockVertexShader");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VertexShaderScriptCommands_VertexShader_as_InputtingNonNullVertexShader_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::Resources::VertexShaderScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    VertexShader vertexShader;
    auto functionResult = state.globals()["VertexShader"]["as"].get<sol::protected_function>().call(&vertexShader, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VertexShaderScriptCommands_VertexShader_as_InputtingNonNullVertexShader_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::Resources::VertexShaderScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["VertexShader"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}