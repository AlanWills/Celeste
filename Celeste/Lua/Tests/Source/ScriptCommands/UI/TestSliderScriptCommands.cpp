#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/UI/SliderScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "UI/Slider.h"
#include "Rendering/SpriteRenderer.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;
using Slider = Celeste::UI::Slider;

using namespace Celeste;
using namespace Celeste::Rendering;


namespace TestCelesteLua::Lua::UI::SliderScriptCommands
{
  CELESTE_TEST_CLASS(TestSliderScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderScriptCommands_Initialize_Adds_SliderUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[Slider::type_name()].valid());

    Celeste::Lua::UI::SliderScriptCommands::initialize(state);

    Assert::IsTrue(state[Slider::type_name()].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderScriptCommands_Initialize_Adds_setCurrentValue_ToSliderTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[Slider::type_name()]["setCurrentValue"].valid());

    Celeste::Lua::UI::SliderScriptCommands::initialize(state);

    Assert::IsTrue(state[Slider::type_name()]["setCurrentValue"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderScriptCommands_Initialize_Adds_subscribeOnValueChangedCallback_ToSliderTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[Slider::type_name()]["subscribeOnValueChangedCallback"].valid());

    Celeste::Lua::UI::SliderScriptCommands::initialize(state);

    Assert::IsTrue(state[Slider::type_name()]["subscribeOnValueChangedCallback"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderScriptCommands_Initialize_Adds_as_ToSliderTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Slider"]["as"].valid());

    Celeste::Lua::UI::SliderScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Slider"]["as"].valid());
  }

#pragma endregion

#pragma region Set Current Value Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderScriptCommands_SetCurrentValue_LessThanMin_SetsValueToMin)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::UI::SliderScriptCommands::initialize(state);

    GameObject gameObject;
    gameObject.addComponent<SpriteRenderer>();
    
    Slider slider(gameObject);
    slider.setMin(0);

    auto result = state[Slider::type_name()]["setCurrentValue"].get<sol::protected_function>().call(slider, -1);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(0.0f, slider.getCurrentValue());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderScriptCommands_SetCurrentValue_GreaterThanMax_SetsValueToMax)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::UI::SliderScriptCommands::initialize(state);

    GameObject gameObject;
    gameObject.addComponent<SpriteRenderer>();
    
    Slider slider(gameObject);
    slider.setMax(100);

    auto result = state[Slider::type_name()]["setCurrentValue"].get<sol::protected_function>().call(slider, 200);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(100.0f, slider.getCurrentValue());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderScriptCommands_SetCurrentValue_InBetweenMinAndMax_ToInputtedValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::UI::SliderScriptCommands::initialize(state);

    GameObject gameObject;
    gameObject.addComponent<SpriteRenderer>();
    
    Slider slider(gameObject);
    slider.setMin(0);
    slider.setMax(100);

    auto result = state[Slider::type_name()]["setCurrentValue"].get<sol::protected_function>().call(slider, 50);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(50.0f, slider.getCurrentValue());
  }

#pragma endregion

#pragma region Subscribe On Value Changed Callback Tests

  void TestSliderScriptCommands::callback(GameObject&, float) {}

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderScriptCommands_SubscribeOnValueChangedCallback_AddsCallback)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::UI::SliderScriptCommands::initialize(state);

    GameObject gameObject;
    Slider slider(gameObject);

    Assert::AreEqual(static_cast<size_t>(0), slider.getValueChangedEvent().getSubscriberCount());

    auto result = state[Slider::type_name()]["subscribeOnValueChangedCallback"].get<sol::protected_function>().call(slider, &TestSliderScriptCommands::callback);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(1), slider.getValueChangedEvent().getSubscriberCount());
  }

#pragma endregion

#pragma region Slider As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderScriptCommands_Slider_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::UI::SliderScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["Slider"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderScriptCommands_Slider_as_InputtingNull_CastingToSliderType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::UI::SliderScriptCommands::initialize(state);

    auto functionResult = state.globals()["Slider"]["as"].get<sol::protected_function>().call(nullptr, "Slider");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderScriptCommands_Slider_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::UI::SliderScriptCommands::initialize(state);

    class MockSlider : public Celeste::UI::Slider {};
    state.new_usertype<MockSlider>("MockSlider");

    auto functionResult = state.globals()["Slider"]["as"].get<sol::protected_function>().call(nullptr, "MockSlider");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderScriptCommands_Slider_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::UI::SliderScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["Slider"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderScriptCommands_SliderHandle_as_InputtingNullSliderHandle_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::UI::SliderScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Slider"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderScriptCommands_Slider_as_InputtingNonNullSlider_CastingToBaseType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::UI::SliderScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    GameObject gameObject;
    Slider slider(gameObject);
    auto functionResult = state.globals()["Slider"]["as"].get<sol::protected_function>().call(&slider, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&slider == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderScriptCommands_Slider_as_InputtingNonNullSlider_CastingToSliderType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::UI::SliderScriptCommands::initialize(state);

    GameObject gameObject;
    Slider slider(gameObject);
    auto functionResult = state.globals()["Slider"]["as"].get<sol::protected_function>().call(&slider, "Slider");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&slider == functionResult.get<Slider*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderScriptCommands_Slider_as_InputtingNonNullSlider_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::UI::SliderScriptCommands::initialize(state);

    class MockSlider : public Celeste::UI::Slider {};
    state.new_usertype<MockSlider>("MockSlider");

    GameObject gameObject;
    Slider slider(gameObject);
    auto functionResult = state.globals()["Slider"]["as"].get<sol::protected_function>().call(&slider, "MockSlider");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderScriptCommands_Slider_as_InputtingNonNullSlider_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::UI::SliderScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    GameObject gameObject;
    Slider slider(gameObject);
    auto functionResult = state.globals()["Slider"]["as"].get<sol::protected_function>().call(&slider, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SliderScriptCommands_Slider_as_InputtingNonNullSlider_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::UI::SliderScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Slider"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}