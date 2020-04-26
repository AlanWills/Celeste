#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "ScriptCommands/Physics/EllipseColliderScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Physics/EllipseCollider.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;
using EllipseCollider = Celeste::Physics::EllipseCollider;

using namespace Celeste;


namespace TestCelesteLua::Lua::Physics::EllipseColliderScriptCommands
{
  CELESTE_TEST_CLASS(TestEllipseColliderScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EllipseColliderScriptCommands_Initialize_Adds_EllipseColliderUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["EllipseCollider"].valid());

    Celeste::Lua::Physics::EllipseColliderScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["EllipseCollider"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EllipseColliderScriptCommands_Initialize_Adds_getDimensions_ToEllipseColliderTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["EllipseCollider"]["getDimensions"].valid());

    Celeste::Lua::Physics::EllipseColliderScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["EllipseCollider"]["getDimensions"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EllipseColliderScriptCommands_Initialize_Adds_setDimensions_ToEllipseColliderTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["EllipseCollider"]["setDimensions"].valid());

    Celeste::Lua::Physics::EllipseColliderScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["EllipseCollider"]["setDimensions"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EllipseColliderScriptCommands_Initialize_Adds_getOffset_ToEllipseColliderTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["EllipseCollider"]["getOffset"].valid());

    Celeste::Lua::Physics::EllipseColliderScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["EllipseCollider"]["getOffset"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EllipseColliderScriptCommands_Initialize_Adds_setOffset_ToEllipseColliderTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["EllipseCollider"]["setOffset"].valid());

    Celeste::Lua::Physics::EllipseColliderScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["EllipseCollider"]["setOffset"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EllipseColliderScriptCommands_Initialize_Adds_getIsTrigger_ToEllipseColliderTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["EllipseCollider"]["getIsTrigger"].valid());

    Celeste::Lua::Physics::EllipseColliderScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["EllipseCollider"]["getIsTrigger"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EllipseColliderScriptCommands_Initialize_Adds_setIsTrigger_ToEllipseColliderTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["EllipseCollider"]["setIsTrigger"].valid());

    Celeste::Lua::Physics::EllipseColliderScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["EllipseCollider"]["setIsTrigger"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EllipseColliderScriptCommands_Initialize_Adds_as_ToEllipseColliderTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["EllipseCollider"]["as"].valid());

    Celeste::Lua::Physics::EllipseColliderScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["EllipseCollider"]["as"].valid());
  }

#pragma endregion

#pragma region EllipseCollider As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EllipseColliderScriptCommands_EllipseCollider_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Physics::EllipseColliderScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["EllipseCollider"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EllipseColliderScriptCommands_EllipseCollider_as_InputtingNull_CastingToEllipseColliderType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Physics::EllipseColliderScriptCommands::initialize(state);

    auto functionResult = state.globals()["EllipseCollider"]["as"].get<sol::protected_function>().call(nullptr, "EllipseCollider");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EllipseColliderScriptCommands_EllipseCollider_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Physics::EllipseColliderScriptCommands::initialize(state);

    class MockEllipseCollider : public Celeste::Physics::EllipseCollider {};
    state.new_usertype<MockEllipseCollider>("MockEllipseCollider");

    auto functionResult = state.globals()["EllipseCollider"]["as"].get<sol::protected_function>().call(nullptr, "MockEllipseCollider");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EllipseColliderScriptCommands_EllipseCollider_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Physics::EllipseColliderScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["EllipseCollider"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EllipseColliderScriptCommands_EllipseColliderHandle_as_InputtingNullEllipseColliderHandle_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Physics::EllipseColliderScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["EllipseCollider"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EllipseColliderScriptCommands_EllipseCollider_as_InputtingNonNullEllipseCollider_CastingToBaseType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Physics::EllipseColliderScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    GameObject gameObject;
    EllipseCollider ellipseCollider(gameObject);
    auto functionResult = state.globals()["EllipseCollider"]["as"].get<sol::protected_function>().call(&ellipseCollider, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&ellipseCollider == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EllipseColliderScriptCommands_EllipseCollider_as_InputtingNonNullEllipseCollider_CastingToEllipseColliderType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Physics::EllipseColliderScriptCommands::initialize(state);

    GameObject gameObject;
    EllipseCollider ellipseCollider(gameObject);
    auto functionResult = state.globals()["EllipseCollider"]["as"].get<sol::protected_function>().call(&ellipseCollider, "EllipseCollider");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&ellipseCollider == functionResult.get<EllipseCollider*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EllipseColliderScriptCommands_EllipseCollider_as_InputtingNonNullEllipseCollider_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Physics::EllipseColliderScriptCommands::initialize(state);

    class MockEllipseCollider : public Celeste::Physics::EllipseCollider {};
    state.new_usertype<MockEllipseCollider>("MockEllipseCollider");

    GameObject gameObject;
    EllipseCollider ellipseCollider(gameObject);
    auto functionResult = state.globals()["EllipseCollider"]["as"].get<sol::protected_function>().call(&ellipseCollider, "MockEllipseCollider");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EllipseColliderScriptCommands_EllipseCollider_as_InputtingNonNullEllipseCollider_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Physics::EllipseColliderScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    GameObject gameObject;
    EllipseCollider ellipseCollider(gameObject);
    auto functionResult = state.globals()["EllipseCollider"]["as"].get<sol::protected_function>().call(&ellipseCollider, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EllipseColliderScriptCommands_EllipseCollider_as_InputtingNonNullEllipseCollider_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Physics::EllipseColliderScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["EllipseCollider"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}