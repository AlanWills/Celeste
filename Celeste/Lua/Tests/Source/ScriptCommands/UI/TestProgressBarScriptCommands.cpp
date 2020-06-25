#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "ScriptCommands/UI/ProgressBarScriptCommands.h"
#include "ScriptCommands/Utils/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "UI/ProgressBar.h"
#include "TestUtils/Assert/AssertCel.h"

using LuaState = Celeste::Lua::LuaState;
using ProgressBar = Celeste::UI::ProgressBar;

using namespace Celeste;


namespace TestCeleste::Lua::UI::ProgressBarScriptCommands
{
  CELESTE_TEST_CLASS(TestProgressBarScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_Initialize_Adds_ProgressBarUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[ProgressBar::type_name()].valid());

    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    Assert::IsTrue(state[ProgressBar::type_name()].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_Initialize_Adds_getProgress_ToProgressBarTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[ProgressBar::type_name()]["getProgress"].valid());

    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    Assert::IsTrue(state[ProgressBar::type_name()]["getProgress"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_Initialize_Adds_setProgress_ToProgressBarTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[ProgressBar::type_name()]["setProgress"].valid());

    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    Assert::IsTrue(state[ProgressBar::type_name()]["setProgress"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_Initialize_Adds_getMin_ToProgressBarTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[ProgressBar::type_name()]["getMin"].valid());

    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    Assert::IsTrue(state[ProgressBar::type_name()]["getMin"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_Initialize_Adds_setMin_ToProgressBarTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[ProgressBar::type_name()]["setMin"].valid());

    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    Assert::IsTrue(state[ProgressBar::type_name()]["setMin"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_Initialize_Adds_getMax_ToProgressBarTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[ProgressBar::type_name()]["getMax"].valid());

    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    Assert::IsTrue(state[ProgressBar::type_name()]["getMax"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_Initialize_Adds_setMax_ToProgressBarTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[ProgressBar::type_name()]["setMax"].valid());

    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    Assert::IsTrue(state[ProgressBar::type_name()]["setMax"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_Initialize_Adds_as_ToProgressBarTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["ProgressBar"]["as"].valid());

    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["ProgressBar"]["as"].valid());
  }

#pragma endregion

#pragma region Get Progress Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_getProgress_ReturnsCorrectProgressValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    GameObject gameObject;
    ProgressBar progressBar(gameObject);
    progressBar.setProgress(0.25f);

    Assert::AreEqual(0.25f, progressBar.getProgress());

    auto result = state[ProgressBar::type_name()]["getProgress"].get<sol::protected_function>().call(progressBar);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(0.25f, result.get<float>());
  }

#pragma endregion

#pragma region Set Progress Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_setProgress_ValueLowerThanMin_SetsProgressToMinValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    GameObject gameObject;
    ProgressBar progressBar(gameObject);
    progressBar.setMin(0);
    progressBar.setProgress(0.25f);

    Assert::AreEqual(0.0f, progressBar.getMin());
    Assert::AreEqual(0.25f, progressBar.getProgress());

    auto result = state[ProgressBar::type_name()]["setProgress"].get<sol::protected_function>().call(progressBar, -1);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(0.0f, progressBar.getProgress());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_setProgress_ValueHigherThanMax_SetsProgressToMaxValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    GameObject gameObject;
    ProgressBar progressBar(gameObject);
    progressBar.setMax(1);
    progressBar.setProgress(0.25f);

    Assert::AreEqual(1.0f, progressBar.getMax());
    Assert::AreEqual(0.25f, progressBar.getProgress());

    auto result = state[ProgressBar::type_name()]["setProgress"].get<sol::protected_function>().call(progressBar, 2);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(1.0f, progressBar.getProgress());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_setProgress_ValueInMinMaxRange_SetsProgressToInputtedValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    GameObject gameObject;
    ProgressBar progressBar(gameObject);
    progressBar.setMin(0);
    progressBar.setMax(1);
    progressBar.setProgress(0.25f);

    Assert::AreEqual(0.0f, progressBar.getMin());
    Assert::AreEqual(1.0f, progressBar.getMax());
    Assert::AreEqual(0.25f, progressBar.getProgress());

    auto result = state[ProgressBar::type_name()]["setProgress"].get<sol::protected_function>().call(progressBar, 0.765f);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(0.765f, progressBar.getProgress());
  }

#pragma endregion

#pragma region Get Min Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_getMin_ReturnsCorrectMinValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    GameObject gameObject;
    ProgressBar progressBar(gameObject);
    progressBar.setMin(-12);

    Assert::AreEqual(-12.0f, progressBar.getMin());

    auto result = state[ProgressBar::type_name()]["getMin"].get<sol::protected_function>().call(progressBar);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(-12.0f, result.get<float>());
  }

#pragma endregion

#pragma region Set Min Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_setMin_UpdatesMinValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    GameObject gameObject;
    ProgressBar progressBar(gameObject);
    progressBar.setMin(0);
    progressBar.setProgress(0.25f);

    Assert::AreEqual(0.0f, progressBar.getMin());
    Assert::AreEqual(0.25f, progressBar.getProgress());

    auto result = state[ProgressBar::type_name()]["setMin"].get<sol::protected_function>().call(progressBar, -1);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(-1.0f, progressBar.getMin());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_setMin_ClampsProgressToAtLeastNewMinValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    GameObject gameObject;
    ProgressBar progressBar(gameObject);
    progressBar.setMin(0);
    progressBar.setProgress(0.25f);

    Assert::AreEqual(0.0f, progressBar.getMin());
    Assert::AreEqual(0.25f, progressBar.getProgress());

    auto result = state[ProgressBar::type_name()]["setMin"].get<sol::protected_function>().call(progressBar, 0.35f);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(0.35f, progressBar.getProgress());
  }

#pragma endregion

#pragma region Get Max Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_getMax_ReturnsCorrectMaxValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    GameObject gameObject;
    ProgressBar progressBar(gameObject);
    progressBar.setMax(0.25f);

    Assert::AreEqual(0.25f, progressBar.getMax());

    auto result = state[ProgressBar::type_name()]["getMax"].get<sol::protected_function>().call(progressBar);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(0.25f, result.get<float>());
  }

#pragma endregion

#pragma region Set Max Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_setMax_UpdatesMaxValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    GameObject gameObject;
    ProgressBar progressBar(gameObject);
    progressBar.setMax(10);
    progressBar.setProgress(0.25f);

    Assert::AreEqual(10.0f, progressBar.getMax());
    Assert::AreEqual(0.25f, progressBar.getProgress());

    auto result = state[ProgressBar::type_name()]["setMax"].get<sol::protected_function>().call(progressBar, 8.12f);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(8.12f, progressBar.getMax());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_setMax_ClampsProgressToAtMostNewMaxValue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    GameObject gameObject;
    ProgressBar progressBar(gameObject);
    progressBar.setMax(10);
    progressBar.setProgress(0.25f);

    Assert::AreEqual(10.0f, progressBar.getMax());
    Assert::AreEqual(0.25f, progressBar.getProgress());

    auto result = state[ProgressBar::type_name()]["setMax"].get<sol::protected_function>().call(progressBar, 0.15f);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(0.15f, progressBar.getProgress());
  }

#pragma endregion

#pragma region ProgressBar As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_ProgressBar_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["ProgressBar"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_ProgressBar_as_InputtingNull_CastingToProgressBarType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    auto functionResult = state.globals()["ProgressBar"]["as"].get<sol::protected_function>().call(nullptr, "ProgressBar");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_ProgressBar_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    class MockProgressBar : public Celeste::UI::ProgressBar {};
    state.new_usertype<MockProgressBar>("MockProgressBar");

    auto functionResult = state.globals()["ProgressBar"]["as"].get<sol::protected_function>().call(nullptr, "MockProgressBar");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_ProgressBar_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["ProgressBar"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_ProgressBarHandle_as_InputtingNullProgressBarHandle_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["ProgressBar"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_ProgressBar_as_InputtingNonNullProgressBar_CastingToBaseType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    GameObject gameObject;
    ProgressBar progressBar(gameObject);
    auto functionResult = state.globals()["ProgressBar"]["as"].get<sol::protected_function>().call(&progressBar, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&progressBar == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_ProgressBar_as_InputtingNonNullProgressBar_CastingToProgressBarType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    GameObject gameObject;
    ProgressBar progressBar(gameObject);
    auto functionResult = state.globals()["ProgressBar"]["as"].get<sol::protected_function>().call(&progressBar, "ProgressBar");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&progressBar == functionResult.get<ProgressBar*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_ProgressBar_as_InputtingNonNullProgressBar_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    class MockProgressBar : public Celeste::UI::ProgressBar {};
    state.new_usertype<MockProgressBar>("MockProgressBar");

    GameObject gameObject;
    ProgressBar progressBar(gameObject);
    auto functionResult = state.globals()["ProgressBar"]["as"].get<sol::protected_function>().call(&progressBar, "MockProgressBar");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_ProgressBar_as_InputtingNonNullProgressBar_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    GameObject gameObject;
    ProgressBar progressBar(gameObject);
    auto functionResult = state.globals()["ProgressBar"]["as"].get<sol::protected_function>().call(&progressBar, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBarScriptCommands_ProgressBar_as_InputtingNonNullProgressBar_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::UI::ProgressBarScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["ProgressBar"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}