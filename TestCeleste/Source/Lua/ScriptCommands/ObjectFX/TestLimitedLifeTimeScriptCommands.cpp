#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/ObjectFX/LimitedLifeTimeScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Screens/Screen.h"
#include "Mocks/ObjectFX/MockLimitedLifeTime.h"
#include "Utils/ObjectUtils.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Lua;


namespace TestCeleste::Lua::LimitedLifeTimeScriptCommands
{
  CELESTE_TEST_CLASS(TestLimitedLifeTimeScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeScriptCommands_Initialize_Adds_LimitedLifeTimeUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[LimitedLifeTime::type_name()].valid());

    Celeste::Lua::LimitedLifeTimeScriptCommands::initialize();

    Assert::IsTrue(state[LimitedLifeTime::type_name()].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeScriptCommands_Initialize_Adds_allocate_ToLimitedLifeTimeTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[LimitedLifeTime::type_name()]["allocate"].valid());

    Celeste::Lua::LimitedLifeTimeScriptCommands::initialize();

    Assert::IsTrue(state[LimitedLifeTime::type_name()]["allocate"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeScriptCommands_Initialize_Adds_setLifeTime_ToLimitedLifeTimeTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[LimitedLifeTime::type_name()]["setLifeTime"].valid());

    Celeste::Lua::LimitedLifeTimeScriptCommands::initialize();

    Assert::IsTrue(state[LimitedLifeTime::type_name()]["setLifeTime"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeScriptCommands_Initialize_Adds_subscribeOnDeathCallback_ToLimitedLifeTimeTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[LimitedLifeTime::type_name()]["subscribeOnDeathCallback"].valid());

    Celeste::Lua::LimitedLifeTimeScriptCommands::initialize();

    Assert::IsTrue(state[LimitedLifeTime::type_name()]["subscribeOnDeathCallback"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeScriptCommands_Initialize_Adds_as_ToLimitedLifeTimeTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["LimitedLifeTime"]["as"].valid());

    Celeste::Lua::LimitedLifeTimeScriptCommands::initialize();

    Assert::IsTrue(state.globals()["LimitedLifeTime"]["as"].valid());
  }

#pragma endregion

#pragma region Set Life Time Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeScriptCommands_SetLifeTime_UpdatesLifeTimeToInputtedValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::LimitedLifeTimeScriptCommands::initialize();

    LimitedLifeTime lifeTime;
    lifeTime.setLifeTime(0);

    Assert::AreEqual(0.0f, lifeTime.getLifeTime());

    auto result = state["LimitedLifeTime"]["setLifeTime"].call(lifeTime, 10.123f);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(10.123f, lifeTime.getLifeTime());
  }

#pragma endregion

#pragma region Subscribe On Death Callback Tests

  void callback(GameObject& gameObject) {}

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeScriptCommands_subscribeOnDeathCallback_AddsOnDeathCallback)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::LimitedLifeTimeScriptCommands::initialize();

    LimitedLifeTime limitedLifeTime;

    Assert::AreEqual(static_cast<size_t>(0), limitedLifeTime.getOnDeathEvent().getSubscriberCount());

    auto result = state[LimitedLifeTime::type_name()]["subscribeOnDeathCallback"].get<sol::protected_function>().call(limitedLifeTime, &TestLimitedLifeTimeScriptCommands::callback);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(1), limitedLifeTime.getOnDeathEvent().getSubscriberCount());
  }

#pragma endregion

#pragma region LimitedLifeTime As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeScriptCommands_LimitedLifeTime_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::LimitedLifeTimeScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["LimitedLifeTime"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeScriptCommands_LimitedLifeTime_as_InputtingNull_CastingToLimitedLifeTimeType_ReturnsNil)
  {
    Celeste::Lua::LimitedLifeTimeScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    auto functionResult = state.globals()["LimitedLifeTime"]["as"].get<sol::protected_function>().call(nullptr, "LimitedLifeTime");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeScriptCommands_LimitedLifeTime_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::LimitedLifeTimeScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockLimitedLifeTime : public Celeste::LimitedLifeTime {};
    state.new_usertype<MockLimitedLifeTime>("MockLimitedLifeTime");

    auto functionResult = state.globals()["LimitedLifeTime"]["as"].get<sol::protected_function>().call(nullptr, "MockLimitedLifeTime");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeScriptCommands_LimitedLifeTime_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::LimitedLifeTimeScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["LimitedLifeTime"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeScriptCommands_LimitedLifeTimeHandle_as_InputtingNullLimitedLifeTimeHandle_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::LimitedLifeTimeScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["LimitedLifeTime"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeScriptCommands_LimitedLifeTime_as_InputtingNonNullLimitedLifeTime_CastingToBaseType_ReturnsCorrectPtr)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::LimitedLifeTimeScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    LimitedLifeTime limitedLifeTime;
    auto functionResult = state.globals()["LimitedLifeTime"]["as"].get<sol::protected_function>().call(&limitedLifeTime, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&limitedLifeTime == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeScriptCommands_LimitedLifeTime_as_InputtingNonNullLimitedLifeTime_CastingToLimitedLifeTimeType_ReturnsCorrectPtr)
  {
    Celeste::Lua::LimitedLifeTimeScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    LimitedLifeTime limitedLifeTime;
    auto functionResult = state.globals()["LimitedLifeTime"]["as"].get<sol::protected_function>().call(&limitedLifeTime, "LimitedLifeTime");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&limitedLifeTime == functionResult.get<LimitedLifeTime*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeScriptCommands_LimitedLifeTime_as_InputtingNonNullLimitedLifeTime_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::LimitedLifeTimeScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockLimitedLifeTime : public Celeste::LimitedLifeTime {};
    state.new_usertype<MockLimitedLifeTime>("MockLimitedLifeTime");

    LimitedLifeTime limitedLifeTime;
    auto functionResult = state.globals()["LimitedLifeTime"]["as"].get<sol::protected_function>().call(&limitedLifeTime, "MockLimitedLifeTime");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeScriptCommands_LimitedLifeTime_as_InputtingNonNullLimitedLifeTime_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::LimitedLifeTimeScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    LimitedLifeTime limitedLifeTime;
    auto functionResult = state.globals()["LimitedLifeTime"]["as"].get<sol::protected_function>().call(&limitedLifeTime, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeScriptCommands_LimitedLifeTime_as_InputtingNonNullLimitedLifeTime_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::LimitedLifeTimeScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["LimitedLifeTime"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}