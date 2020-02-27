#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Objects/EntityScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Mocks/Objects/MockEntity.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;


namespace TestCeleste::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestEntityScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Initialize_Adds_EntityUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Entity"].valid());

    Celeste::Lua::EntityScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Entity"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Initialize_AddsisActive_ToEntityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Entity"]["isActive"].valid());

    Celeste::Lua::EntityScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Entity"]["isActive"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Initialize_Adds_setActive_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Entity"]["setActive"].valid());

    Celeste::Lua::EntityScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Entity"]["setActive"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Initialize_Adds_die_ToEntityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Entity"]["die"].valid());

    Celeste::Lua::EntityScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Entity"]["die"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Initialize_Adds_as_ToEntityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Entity"]["as"].valid());

    Celeste::Lua::EntityScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Entity"]["as"].valid());
  }

#pragma endregion

#pragma region Is Active Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_isActive_ReturnsObjectActivationStatus)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::EntityScriptCommands::initialize();

    MockEntity entity;
    entity.setActive(false);

    Assert::IsFalse(entity.isActive());

    auto result = state.globals()["Entity"]["isActive"].get<sol::protected_function>().call(static_cast<Entity&>(entity));

    Assert::IsTrue(result.valid());
    Assert::IsFalse(result.get<bool>());

    entity.setActive(true);

    Assert::IsTrue(entity.isActive());

    result = state.globals()["Entity"]["isActive"].get<sol::protected_function>().call(static_cast<Entity&>(entity));

    Assert::IsTrue(result.valid());
    Assert::IsTrue(result.get<bool>());
  }

#pragma endregion

#pragma region Set Active Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_setActive_UpdatesActiveFlagCorrectly)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::EntityScriptCommands::initialize();

    Entity entity;
    
    Assert::IsFalse(entity.isActive());

    auto functionResult = state.globals()["Entity"]["setActive"].get<sol::protected_function>().call(
      entity, true);

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(entity.isActive());

    functionResult = state.globals()["Entity"]["setActive"].get<sol::protected_function>().call(
      entity, false);

    Assert::IsTrue(functionResult.valid());
    Assert::IsFalse(entity.isActive());
  }

#pragma endregion

#pragma region Entity As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Entity_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::EntityScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["Entity"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Entity_as_InputtingNull_CastingToEntityType_ReturnsNil)
  {
    Celeste::Lua::EntityScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    auto functionResult = state.globals()["Entity"]["as"].get<sol::protected_function>().call(nullptr, "Entity");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Entity_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::EntityScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockEntity : public Celeste::Entity {};
    state.new_usertype<MockEntity>("MockEntity");

    auto functionResult = state.globals()["Entity"]["as"].get<sol::protected_function>().call(nullptr, "MockEntity");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Entity_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::EntityScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["Entity"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_EntityHandle_as_InputtingNullEntityHandle_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::EntityScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Entity"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Entity_as_InputtingNonNullEntity_CastingToBaseType_ReturnsCorrectPtr)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::EntityScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    Entity entity;
    auto functionResult = state.globals()["Entity"]["as"].get<sol::protected_function>().call(&entity, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&entity == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Entity_as_InputtingNonNullEntity_CastingToEntityType_ReturnsCorrectPtr)
  {
    Celeste::Lua::EntityScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Entity entity;
    auto functionResult = state.globals()["Entity"]["as"].get<sol::protected_function>().call(&entity, "Entity");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&entity == functionResult.get<Entity*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Entity_as_InputtingNonNullEntity_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::EntityScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockEntity : public Celeste::Entity {};
    state.new_usertype<MockEntity>("MockEntity");

    Entity entity;
    auto functionResult = state.globals()["Entity"]["as"].get<sol::protected_function>().call(&entity, "MockEntity");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Entity_as_InputtingNonNullEntity_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::EntityScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    Entity entity;
    auto functionResult = state.globals()["Entity"]["as"].get<sol::protected_function>().call(&entity, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Entity_as_InputtingNonNullEntity_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::EntityScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Entity"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}