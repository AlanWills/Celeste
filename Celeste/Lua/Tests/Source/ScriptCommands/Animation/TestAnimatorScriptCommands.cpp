#include "ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "ScriptCommands/Animation/AnimatorScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "UtilityHeaders/UnitTestHeaders.h"
#include "AssertCel.h"

#include "Mocks/Animation/MockAnimator.h"

using namespace Celeste;
using LuaState = Celeste::Lua::LuaState;
using Animator = Celeste::Animation::Animator;


namespace TestCelesteLua::Lua::Animation::AnimatorScriptCommands
{
  CELESTE_TEST_CLASS(TestAnimatorScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Initialize_Adds_AnimatorUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Animator"].valid());

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Animator"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Initialize_Adds_getSpriteSheetDimensions_ToAnimatorTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Animator"]["getSpriteSheetDimensions"].valid());

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Animator"]["getSpriteSheetDimensions"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Initialize_Adds_setSpriteSheetDimensions_ToAnimatorTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Animator"]["setSpriteSheetDimensions"].valid());

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Animator"]["setSpriteSheetDimensions"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Initialize_Adds_getSecondsPerFrame_ToAnimatorTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Animator"]["getSecondsPerFrame"].valid());

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Animator"]["getSecondsPerFrame"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Initialize_Adds_setSecondsPerFrame_ToAnimatorTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Animator"]["setSecondsPerFrame"].valid());

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Animator"]["setSecondsPerFrame"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Initialize_Adds_isLooping_ToAnimatorTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Animator"]["isLooping"].valid());

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Animator"]["isLooping"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Initialize_Adds_setLooping_ToAnimatorTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Animator"]["setLooping"].valid());

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Animator"]["setLooping"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Initialize_Adds_as_ToAnimatorTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Animator"]["as"].valid());

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Animator"]["as"].valid());
  }

#pragma endregion

#pragma region Animator As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Animator_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Animation::AnimatorScriptCommands::initialize(state);

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["Animator"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Animator_as_InputtingNull_CastingToAnimatorType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize(state);

    auto functionResult = state.globals()["Animator"]["as"].get<sol::protected_function>().call(nullptr, "Animator");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Animator_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize(state);

    class MockAnimator : public Celeste::Animation::Animator {};
    state.new_usertype<MockAnimator>("MockAnimator");

    auto functionResult = state.globals()["Animator"]["as"].get<sol::protected_function>().call(nullptr, "MockAnimator");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Animator_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["Animator"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_AnimatorHandle_as_InputtingNullAnimatorHandle_CastingToNonExistentType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Animator"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Animator_as_InputtingNonNullAnimator_CastingToBaseType_ReturnsCorrectPtr)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::registerUserType<Object>(state, "Object");
    Celeste::Lua::Animation::AnimatorScriptCommands::initialize(state);

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
    sol::state& state = LuaState::instance();

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize(state);

    GameObject gameObject;
    Animator animator(gameObject);
    auto functionResult = state.globals()["Animator"]["as"].get<sol::protected_function>().call(&animator, "Animator");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&animator == functionResult.get<Animator*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimatorScriptCommands_Animator_as_InputtingNonNullAnimator_CastingToDerivedType_ReturnsNil)
  {
    sol::state& state = LuaState::instance();

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize(state);

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
    sol::state& state = LuaState::instance();

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize(state);

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>(state, "UnrelatedType");

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
    sol::state& state = LuaState::instance();

    Celeste::Lua::Animation::AnimatorScriptCommands::initialize(state);

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Animator"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}