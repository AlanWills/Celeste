#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "Lua/ScriptCommands/Resources/2D/Texture2DScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Mocks/Resources/2D/MockTexture2D.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;

using namespace Celeste;
using namespace Celeste::Resources;


namespace TestCeleste::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestTexture2DScriptCommands)

#pragma region Initialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Texture2DScriptCommands_Initialize_Adds_Texture2DUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Texture2D"].valid());

    Celeste::Lua::Resources::Texture2DScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Texture2D"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Texture2DScriptCommands_Initialize_Adds_as_ToTexture2DTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Texture2D"]["as"].valid());

    Celeste::Lua::Resources::Texture2DScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Texture2D"]["as"].valid());
  }

#pragma endregion

#pragma region Texture2D As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Texture2DScriptCommands_Texture2D_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::Resources::Texture2DScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["Texture2D"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Texture2DScriptCommands_Texture2D_as_InputtingNull_CastingToTexture2DType_ReturnsNil)
  {
    Celeste::Lua::Resources::Texture2DScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    auto functionResult = state.globals()["Texture2D"]["as"].get<sol::protected_function>().call(nullptr, "Texture2D");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Texture2DScriptCommands_Texture2D_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::Resources::Texture2DScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockTexture2D : public Celeste::Resources::Texture2D {};
    state.new_usertype<MockTexture2D>("MockTexture2D");

    auto functionResult = state.globals()["Texture2D"]["as"].get<sol::protected_function>().call(nullptr, "MockTexture2D");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Texture2DScriptCommands_Texture2D_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::Resources::Texture2DScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["Texture2D"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Texture2DScriptCommands_Texture2DHandle_as_InputtingNullTexture2DHandle_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::Resources::Texture2DScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Texture2D"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Texture2DScriptCommands_Texture2D_as_InputtingNonNullTexture2D_CastingToBaseType_ReturnsCorrectPtr)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::Resources::Texture2DScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    Texture2D texture2D;
    auto functionResult = state.globals()["Texture2D"]["as"].get<sol::protected_function>().call(&texture2D, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&texture2D == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Texture2DScriptCommands_Texture2D_as_InputtingNonNullTexture2D_CastingToTexture2DType_ReturnsCorrectPtr)
  {
    Celeste::Lua::Resources::Texture2DScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Texture2D texture2D;
    auto functionResult = state.globals()["Texture2D"]["as"].get<sol::protected_function>().call(&texture2D, "Texture2D");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&texture2D == functionResult.get<Texture2D*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Texture2DScriptCommands_Texture2D_as_InputtingNonNullTexture2D_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::Resources::Texture2DScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockTexture2D : public Celeste::Resources::Texture2D {};
    state.new_usertype<MockTexture2D>("MockTexture2D");

    Texture2D texture2D;
    auto functionResult = state.globals()["Texture2D"]["as"].get<sol::protected_function>().call(&texture2D, "MockTexture2D");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Texture2DScriptCommands_Texture2D_as_InputtingNonNullTexture2D_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::Resources::Texture2DScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    Texture2D texture2D;
    auto functionResult = state.globals()["Texture2D"]["as"].get<sol::protected_function>().call(&texture2D, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Texture2DScriptCommands_Texture2D_as_InputtingNonNullTexture2D_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::Resources::Texture2DScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Texture2D"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}