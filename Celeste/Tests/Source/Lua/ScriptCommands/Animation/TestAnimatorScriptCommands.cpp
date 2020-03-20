#include "Lua/ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "Lua/ScriptCommands/Animation/AnimatorScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "UtilityHeaders/UnitTestHeaders.h"
#include "AssertCel.h"

#include "Mocks/Animation/MockAnimator.h"

using namespace Celeste;
using LuaState = Celeste::Lua::LuaState;
using Animator = Celeste::Animation::Animator;


namespace TestCeleste::Lua::Animation::AnimatorScriptCommands
{
  CELESTE_TEST_CLASS(TestAnimatorScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Initialize_Adds_AnimatorUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Animator"].valid());

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Animator"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Initialize_Adds_getSpriteSheetDimensions_ToAnimatorTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Animator"]["getSpriteSheetDimensions"].valid());

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Animator"]["getSpriteSheetDimensions"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Initialize_Adds_setSpriteSheetDimensions_ToAnimatorTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Animator"]["setSpriteSheetDimensions"].valid());

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Animator"]["setSpriteSheetDimensions"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Initialize_Adds_getSecondsPerFrame_ToAnimatorTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Animator"]["getSecondsPerFrame"].valid());

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Animator"]["getSecondsPerFrame"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Initialize_Adds_setSecondsPerFrame_ToAnimatorTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Animator"]["setSecondsPerFrame"].valid());

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Animator"]["setSecondsPerFrame"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Initialize_Adds_isLooping_ToAnimatorTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Animator"]["isLooping"].valid());

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Animator"]["isLooping"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Initialize_Adds_setLooping_ToAnimatorTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Animator"]["setLooping"].valid());

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Animator"]["setLooping"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Initialize_Adds_as_ToAnimatorTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Animator"]["as"].valid());

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Animator"]["as"].valid());
  }

#pragma endregion

#pragma region Animator As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Animator_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::Animation::AnimatorScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["Animator"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Animator_as_InputtingNull_CastingToAnimatorType_ReturnsNil)
  {
    Celeste::Lua::Animation::AnimatorScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    auto functionResult = state.globals()["Animator"]["as"].get<sol::protected_function>().call(nullptr, "Animator");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Animator_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::Animation::AnimatorScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockAnimator : public Celeste::Animation::Animator {};
    state.new_usertype<MockAnimator>("MockAnimator");

    auto functionResult = state.globals()["Animator"]["as"].get<sol::protected_function>().call(nullptr, "MockAnimator");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Animator_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::Animation::AnimatorScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["Animator"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_AnimatorHandle_as_InputtingNullAnimatorHandle_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::Animation::AnimatorScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Animator"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Animator_as_InputtingNonNullAnimator_CastingToBaseType_ReturnsCorrectPtr)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::Animation::AnimatorScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    GameObject gameObject;
    Animator animator(gameObject);
    auto functionResult = state.globals()["Animator"]["as"].get<sol::protected_function>().call(&animator, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&animator == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Animator_as_InputtingNonNullAnimator_CastingToAnimatorType_ReturnsCorrectPtr)
  {
    Celeste::Lua::Animation::AnimatorScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    GameObject gameObject;
    Animator animator(gameObject);
    auto functionResult = state.globals()["Animator"]["as"].get<sol::protected_function>().call(&animator, "Animator");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&animator == functionResult.get<Animator*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Animator_as_InputtingNonNullAnimator_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::Animation::AnimatorScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockAnimator : public Celeste::Animation::Animator {};
    state.new_usertype<MockAnimator>("MockAnimator");

    GameObject gameObject;
    Animator animator(gameObject);
    auto functionResult = state.globals()["Animator"]["as"].get<sol::protected_function>().call(&animator, "MockAnimator");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Animator_as_InputtingNonNullAnimator_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::Animation::AnimatorScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    GameObject gameObject;
    Animator animator(gameObject);
    auto functionResult = state.globals()["Animator"]["as"].get<sol::protected_function>().call(&animator, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Animator_as_InputtingNonNullAnimator_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::Animation::AnimatorScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Animator"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}