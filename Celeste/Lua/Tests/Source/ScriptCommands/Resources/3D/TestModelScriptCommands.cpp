#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "ScriptCommands/Resources/3D/ModelScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Mocks/Resources/3D/MockModel.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;

using namespace Celeste;
using namespace Celeste::Resources;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestModelScriptCommands)

#pragma region Initialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ModelScriptCommands_Initialize_Adds_ModelUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Model"].valid());

    Celeste::Lua::Resources::ModelScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Model"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ModelScriptCommands_Initialize_Adds_as_ToModelTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Model"]["as"].valid());

    Celeste::Lua::Resources::ModelScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Model"]["as"].valid());
  }

#pragma endregion

#pragma region Model As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ModelScriptCommands_Model_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Resources::ModelScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["Model"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ModelScriptCommands_Model_as_InputtingNull_CastingToModelType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::ModelScriptCommands::initialize(state);

    auto functionResult = state.globals()["Model"]["as"].get<sol::protected_function>().call(nullptr, "Model");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ModelScriptCommands_Model_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::ModelScriptCommands::initialize(state);

    class MockModel : public Celeste::Resources::Model {};
    state.new_usertype<MockModel>("MockModel");

    auto functionResult = state.globals()["Model"]["as"].get<sol::protected_function>().call(nullptr, "MockModel");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ModelScriptCommands_Model_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::ModelScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["Model"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ModelScriptCommands_ModelHandle_as_InputtingNullModelHandle_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::ModelScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Model"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ModelScriptCommands_Model_as_InputtingNonNullModel_CastingToBaseType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Resources::ModelScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    Model model;
    auto functionResult = state.globals()["Model"]["as"].get<sol::protected_function>().call(&model, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&model == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ModelScriptCommands_Model_as_InputtingNonNullModel_CastingToModelType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::ModelScriptCommands::initialize(state);

    Model model;
    auto functionResult = state.globals()["Model"]["as"].get<sol::protected_function>().call(&model, "Model");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&model == functionResult.get<Model*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ModelScriptCommands_Model_as_InputtingNonNullModel_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::ModelScriptCommands::initialize(state);

    class MockModel : public Celeste::Resources::Model {};
    state.new_usertype<MockModel>("MockModel");

    Model model;
    auto functionResult = state.globals()["Model"]["as"].get<sol::protected_function>().call(&model, "MockModel");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ModelScriptCommands_Model_as_InputtingNonNullModel_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::ModelScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    Model model;
    auto functionResult = state.globals()["Model"]["as"].get<sol::protected_function>().call(&model, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ModelScriptCommands_Model_as_InputtingNonNullModel_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Resources::ModelScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Model"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}