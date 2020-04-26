#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "ScriptCommands/Objects/ComponentScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Mocks/Objects/MockComponent.h"

#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestComponentScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentScriptCommands_Initialize_Adds_ComponentUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Component"].valid());

    Celeste::Lua::ComponentScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Component"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentScriptCommands_Initialize_Adds_as_ToComponentTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Component"]["as"].valid());

    Celeste::Lua::ComponentScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Component"]["as"].valid());
  }

#pragma endregion

#pragma region Component As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentScriptCommands_Component_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::ComponentScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["Component"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentScriptCommands_Component_as_InputtingNull_CastingToComponentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::ComponentScriptCommands::initialize(state);

    auto functionResult = state.globals()["Component"]["as"].get<sol::protected_function>().call(nullptr, "Component");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentScriptCommands_Component_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::ComponentScriptCommands::initialize(state);

    class MockComponent : public Celeste::Component {};
    state.new_usertype<MockComponent>("MockComponent");

    auto functionResult = state.globals()["Component"]["as"].get<sol::protected_function>().call(nullptr, "MockComponent");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentScriptCommands_Component_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::ComponentScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["Component"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentScriptCommands_ComponentHandle_as_InputtingNullComponentHandle_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::ComponentScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Component"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentScriptCommands_Component_as_InputtingNonNullComponent_CastingToBaseType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::ComponentScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    GameObject gameObject;
    MockComponent mockComponent(gameObject);
    Component* component = static_cast<Component*>(&mockComponent);
    auto functionResult = state.globals()["Component"]["as"].get<sol::protected_function>().call(component, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&mockComponent == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentScriptCommands_Component_as_InputtingNonNullComponent_CastingToComponentType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::ComponentScriptCommands::initialize(state);

    GameObject gameObject;
    MockComponent mockComponent(gameObject);
    Component* component = static_cast<Component*>(&mockComponent);
    auto functionResult = state.globals()["Component"]["as"].get<sol::protected_function>().call(component, "Component");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&mockComponent == functionResult.get<Component*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentScriptCommands_Component_as_InputtingNonNullComponent_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::ComponentScriptCommands::initialize(state);

    class DerivedComponent : public MockComponent {};
    state.new_usertype<DerivedComponent>("DerivedComponent");

    GameObject gameObject;
    MockComponent mockComponent(gameObject);
    Component* component = static_cast<Component*>(&mockComponent);
    auto functionResult = state.globals()["Component"]["as"].get<sol::protected_function>().call(component, "DerivedComponent");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentScriptCommands_Component_as_InputtingNonNullComponent_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::ComponentScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    GameObject gameObject;
    MockComponent mockComponent(gameObject);
    Component* component = static_cast<Component*>(&mockComponent);
    auto functionResult = state.globals()["Component"]["as"].get<sol::protected_function>().call(component, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentScriptCommands_Component_as_InputtingNonNullComponent_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::ComponentScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Component"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}