#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "Lua/ScriptCommands/Resources/Data/DataScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Mocks/Resources/Data/MockData.h"

#include "Utils/ObjectUtils.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;

using namespace Celeste;
using namespace Celeste::Resources;


namespace TestCeleste::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestDataScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataScriptCommands_Initialize_Adds_DataUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Data"].valid());

    Celeste::Lua::Resources::DataScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Data"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataScriptCommands_Initialize_Adds_as_ToDataTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Data"]["as"].valid());

    Celeste::Lua::Resources::DataScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Data"]["as"].valid());
  }

#pragma endregion

#pragma region Data As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataScriptCommands_Data_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::Resources::DataScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["Data"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataScriptCommands_Data_as_InputtingNull_CastingToDataType_ReturnsNil)
  {
    Celeste::Lua::Resources::DataScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    auto functionResult = state.globals()["Data"]["as"].get<sol::protected_function>().call(nullptr, "Data");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataScriptCommands_Data_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::Resources::DataScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockData : public Celeste::Resources::Data {};
    state.new_usertype<MockData>("MockData");

    auto functionResult = state.globals()["Data"]["as"].get<sol::protected_function>().call(nullptr, "MockData");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataScriptCommands_Data_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::Resources::DataScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["Data"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataScriptCommands_DataHandle_as_InputtingNullDataHandle_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::Resources::DataScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Data"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataScriptCommands_Data_as_InputtingNonNullData_CastingToBaseType_ReturnsCorrectPtr)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::Resources::DataScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    Data data;
    auto functionResult = state.globals()["Data"]["as"].get<sol::protected_function>().call(&data, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&data == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataScriptCommands_Data_as_InputtingNonNullData_CastingToDataType_ReturnsCorrectPtr)
  {
    Celeste::Lua::Resources::DataScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Data data;
    auto functionResult = state.globals()["Data"]["as"].get<sol::protected_function>().call(&data, "Data");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&data == functionResult.get<Data*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataScriptCommands_Data_as_InputtingNonNullData_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::Resources::DataScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockData : public Celeste::Resources::Data {};
    state.new_usertype<MockData>("MockData");

    Data data;
    auto functionResult = state.globals()["Data"]["as"].get<sol::protected_function>().call(&data, "MockData");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataScriptCommands_Data_as_InputtingNonNullData_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::Resources::DataScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    Data data;
    auto functionResult = state.globals()["Data"]["as"].get<sol::protected_function>().call(&data, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataScriptCommands_Data_as_InputtingNonNullData_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::Resources::DataScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Data"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}