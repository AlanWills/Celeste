#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Objects/EntityScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Mocks/Objects/MockEntity.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestEntityScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Initialize_Adds_EntityUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Entity"].valid());

    Celeste::Lua::EntityScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Entity"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Initialize_Adds_destroy_ToEntityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Entity"]["destroy"].valid());

    Celeste::Lua::EntityScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Entity"]["destroy"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Initialize_AddsisActive_ToEntityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Entity"]["isActive"].valid());

    Celeste::Lua::EntityScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Entity"]["isActive"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Initialize_Adds_setActive_ToGameObjectTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Entity"]["setActive"].valid());

    Celeste::Lua::EntityScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Entity"]["setActive"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Initialize_Adds_as_ToEntityTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Entity"]["as"].valid());

    Celeste::Lua::EntityScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Entity"]["as"].valid());
  }

#pragma endregion

#pragma region Is Active Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_isActive_ReturnsObjectActivationStatus)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::EntityScriptCommands::initialize(state);

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
    Celeste::Lua::EntityScriptCommands::initialize(state);

    Entity entity;
    
    Assert::IsTrue(entity.isActive());

    auto functionResult = state.globals()["Entity"]["setActive"].get<sol::protected_function>().call(
      entity, false);

    Assert::IsTrue(functionResult.valid());
    Assert::IsFalse(entity.isActive());

    functionResult = state.globals()["Entity"]["setActive"].get<sol::protected_function>().call(
      entity, true);

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(entity.isActive());
  }

#pragma endregion

#pragma region Entity As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Entity_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::EntityScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["Entity"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Entity_as_InputtingNull_CastingToEntityType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::EntityScriptCommands::initialize(state);

    auto functionResult = state.globals()["Entity"]["as"].get<sol::protected_function>().call(nullptr, "Entity");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Entity_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::EntityScriptCommands::initialize(state);

    class MockEntity : public Celeste::Entity {};
    state.new_usertype<MockEntity>("MockEntity");

    auto functionResult = state.globals()["Entity"]["as"].get<sol::protected_function>().call(nullptr, "MockEntity");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Entity_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::EntityScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["Entity"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_EntityHandle_as_InputtingNullEntityHandle_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::EntityScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Entity"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Entity_as_InputtingNonNullEntity_CastingToBaseType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::EntityScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    Entity entity;
    auto functionResult = state.globals()["Entity"]["as"].get<sol::protected_function>().call(&entity, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&entity == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Entity_as_InputtingNonNullEntity_CastingToEntityType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::EntityScriptCommands::initialize(state);

    Entity entity;
    auto functionResult = state.globals()["Entity"]["as"].get<sol::protected_function>().call(&entity, "Entity");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&entity == functionResult.get<Entity*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Entity_as_InputtingNonNullEntity_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::EntityScriptCommands::initialize(state);

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
    sol::state& state = LuaState::instance();

    Celeste::Lua::EntityScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    Entity entity;
    auto functionResult = state.globals()["Entity"]["as"].get<sol::protected_function>().call(&entity, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EntityScriptCommands_Entity_as_InputtingNonNullEntity_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::EntityScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Entity"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}