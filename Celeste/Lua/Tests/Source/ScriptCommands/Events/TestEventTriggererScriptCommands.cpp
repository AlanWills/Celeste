#include "UtilityHeaders/UnitTestHeaders.h"
#include "ScriptCommands/Events/EventTriggererScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Objects/GameObject.h"
#include "Events/EventTriggerer.h"

using namespace Celeste;
using namespace Celeste::Lua;
using namespace Celeste::Events;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestEventTriggererScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_Initialize_AddsEventTriggerer_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();
    
    Assert::IsFalse(state[EventTriggerer::type_name()].valid());

    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);

    Assert::IsTrue(state[EventTriggerer::type_name()].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_Initialize_Adds_getTriggerDelay_ToEventTriggerTable)
  {
    sol::state& state = LuaState::instance();
    
    Assert::IsFalse(state[EventTriggerer::type_name()].valid());

    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);

    Assert::IsTrue(state[EventTriggerer::type_name()]["getTriggerDelay"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_Initialize_Adds_setTriggerDelay_ToEventTriggerTable)
  {
    sol::state& state = LuaState::instance();
    
    Assert::IsFalse(state[EventTriggerer::type_name()].valid());

    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);

    Assert::IsTrue(state[EventTriggerer::type_name()]["setTriggerDelay"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_Initialize_Adds_getTriggerKey_ToEventTriggerTable)
  {
    sol::state& state = LuaState::instance();
    
    Assert::IsFalse(state[EventTriggerer::type_name()].valid());

    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);

    Assert::IsTrue(state[EventTriggerer::type_name()]["getTriggerKey"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_Initialize_Adds_setTriggerKey_ToEventTriggerTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[EventTriggerer::type_name()].valid());

    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);

    Assert::IsTrue(state[EventTriggerer::type_name()]["setTriggerKey"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_Initialize_Adds_getTriggerMode_ToEventTriggerTable)
  {
    sol::state& state = LuaState::instance();
    
    Assert::IsFalse(state[EventTriggerer::type_name()].valid());

    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);

    Assert::IsTrue(state[EventTriggerer::type_name()]["getTriggerMode"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_Initialize_Adds_setTriggerMode_ToEventTriggerTable)
  {
    sol::state& state = LuaState::instance();
    
    Assert::IsFalse(state[EventTriggerer::type_name()].valid());

    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);

    Assert::IsTrue(state[EventTriggerer::type_name()]["setTriggerMode"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_Initialize_Adds_subscribeOnEventTriggered_ToEventTriggerTable)
  {
    sol::state& state = LuaState::instance();
    
    Assert::IsFalse(state[EventTriggerer::type_name()].valid());

    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);

    Assert::IsTrue(state[EventTriggerer::type_name()]["subscribeOnEventTriggeredCallback"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_Initialize_Adds_as_ToEventTriggerTable)
  {
    sol::state& state = LuaState::instance();
    
    Assert::IsFalse(state[EventTriggerer::type_name()].valid());

    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);

    Assert::IsTrue(state[EventTriggerer::type_name()]["as"].valid());
  }

#pragma endregion

#pragma region Get Trigger Delay Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_getTriggerDelay_ReturnsCorrectValue)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();
    eventTriggerer->setTriggerDelay(3);

    sol::state& state = LuaState::instance();
    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);
    auto result = state[EventTriggerer::type_name()]["getTriggerDelay"].get<sol::protected_function>().call(*eventTriggerer);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(3.0f, result.get<float>());
  }

#pragma endregion

#pragma region Set Trigger Delay Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_setTriggerDelay_UpdatesTriggerDelayToCorrectValue)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();
    eventTriggerer->setTriggerDelay(3);

    sol::state& state = LuaState::instance();
    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);
    auto result = state[EventTriggerer::type_name()]["setTriggerDelay"].get<sol::protected_function>().call(*eventTriggerer, 5);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(5.0f, eventTriggerer->getTriggerDelay());
  }

#pragma endregion

#pragma region Get Trigger Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_getTriggerKey_ReturnsCorrectValue)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();
    eventTriggerer->setTriggerKey(GLFW_KEY_A);

    sol::state& state = LuaState::instance();
    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);
    auto result = state[EventTriggerer::type_name()]["getTriggerKey"].get<sol::protected_function>().call(*eventTriggerer);

    Assert::IsTrue(result.valid());
    Assert::AreEqual("A", result.get<std::string>().c_str());
  }

#pragma endregion

#pragma region Set Trigger Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_setTriggerKey_InputtingInvalidValue_DoesNotChangeCurrentTriggerKey)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();
    eventTriggerer->setTriggerKey(GLFW_KEY_B);

    sol::state& state = LuaState::instance();
    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);
    auto result = state[EventTriggerer::type_name()]["setTriggerKey"].get<sol::protected_function>().call(*eventTriggerer, "WubbaLubbaDubDub");

    Assert::IsTrue(result.valid());
    Assert::AreEqual(GLFW_KEY_B, eventTriggerer->getTriggerKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_setTriggerKey_InputtingValidValue_UpdatesTriggerKeyToCorrectValue)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();
    eventTriggerer->setTriggerKey(GLFW_KEY_B);

    sol::state& state = LuaState::instance();
    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);
    auto result = state[EventTriggerer::type_name()]["setTriggerKey"].get<sol::protected_function>().call(*eventTriggerer, "A");

    Assert::IsTrue(result.valid());
    Assert::AreEqual(GLFW_KEY_A, eventTriggerer->getTriggerKey());
  }

#pragma endregion

#pragma region Get Trigger Mode Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_getTriggerMode_InputtingValidValue_ReturnsCorrectValue)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();
    eventTriggerer->setTriggerMode(TriggerMode::kOnce);

    sol::state& state = LuaState::instance();
    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);
    auto result = state[EventTriggerer::type_name()]["getTriggerMode"].get<sol::protected_function>().call(*eventTriggerer);

    Assert::IsTrue(result.valid());
    Assert::IsTrue(TriggerMode::kOnce == result.get<TriggerMode>());
  }

#pragma endregion

#pragma region Set Trigger Mode Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_setTriggerMode_InputtingInvalidValue_DoesNotChangeCurrentTriggerMode)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();
    eventTriggerer->setTriggerMode(TriggerMode::kOnce);

    sol::state& state = LuaState::instance();
    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);
    auto result = state[EventTriggerer::type_name()]["setTriggerMode"].get<sol::protected_function>().call(*eventTriggerer, "WubbaLubbaDubDub");

    Assert::IsTrue(result.valid());
    Assert::IsTrue(TriggerMode::kOnce == eventTriggerer->getTriggerMode());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_setTriggerMode_UpdatesTriggerModeToCorrectValue)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();
    eventTriggerer->setTriggerMode(TriggerMode::kOnce);

    sol::state& state = LuaState::instance();
    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);
    auto result = state[EventTriggerer::type_name()]["setTriggerMode"].get<sol::protected_function>().call(*eventTriggerer, "Unlimited");

    Assert::IsTrue(result.valid());
    Assert::IsTrue(TriggerMode::kUnlimited == eventTriggerer->getTriggerMode());
  }

#pragma endregion

#pragma region Subscribe On Event Triggered Callback Tests

  void TestEventTriggererScriptCommands::callback(const GameObject& /*gameObject*/) {}

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_subscribeOnEventTriggered_SubscribesToEvent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();

    sol::state& state = LuaState::instance();
    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);
    auto result = state[EventTriggerer::type_name()]["subscribeOnEventTriggeredCallback"].
      get<sol::protected_function>().call(*eventTriggerer, &TestEventTriggererScriptCommands::callback, sol::object());

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(1), eventTriggerer->getEvent().getSubscriberCount());
  }

#pragma endregion

#pragma region Event Triggerer As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_EventTriggerer_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["EventTriggerer"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_EventTriggerer_as_InputtingNull_CastingToEventTriggererType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);

    auto functionResult = state.globals()["EventTriggerer"]["as"].get<sol::protected_function>().call(nullptr, "EventTriggerer");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_EventTriggerer_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);

    class DummyEventTriggerer : public Celeste::Events::EventTriggerer {};
    state.new_usertype<DummyEventTriggerer>("MockEventTriggerer");

    auto functionResult = state.globals()["EventTriggerer"]["as"].get<sol::protected_function>().call(nullptr, "DummyEventTriggerer");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_EventTriggerer_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["EventTriggerer"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_EventTriggererHandle_as_InputtingNullEventTriggererHandle_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["EventTriggerer"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_EventTriggerer_as_InputtingNonNullEventTriggerer_CastingToBaseType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    GameObject gameObject;
    EventTriggerer progressBar(gameObject);
    auto functionResult = state.globals()["EventTriggerer"]["as"].get<sol::protected_function>().call(&progressBar, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&progressBar == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_EventTriggerer_as_InputtingNonNullEventTriggerer_CastingToEventTriggererType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);

    GameObject gameObject;
    EventTriggerer progressBar(gameObject);
    auto functionResult = state.globals()["EventTriggerer"]["as"].get<sol::protected_function>().call(&progressBar, "EventTriggerer");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&progressBar == functionResult.get<EventTriggerer*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_EventTriggerer_as_InputtingNonNullEventTriggerer_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);

    class DummyEventTriggerer : public Celeste::Events::EventTriggerer {};
    state.new_usertype<DummyEventTriggerer>("DummyEventTriggerer");

    GameObject gameObject;
    EventTriggerer progressBar(gameObject);
    auto functionResult = state.globals()["EventTriggerer"]["as"].get<sol::protected_function>().call(&progressBar, "DummyEventTriggerer");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_EventTriggerer_as_InputtingNonNullEventTriggerer_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    GameObject gameObject;
    EventTriggerer progressBar(gameObject);
    auto functionResult = state.globals()["EventTriggerer"]["as"].get<sol::protected_function>().call(&progressBar, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggererScriptCommands_EventTriggerer_as_InputtingNonNullEventTriggerer_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Events::EventTriggererScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["EventTriggerer"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}