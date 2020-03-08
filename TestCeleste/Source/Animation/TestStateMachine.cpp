#include "UtilityHeaders/UnitTestHeaders.h"
#include "Registries/ComponentRegistry.h"

#include "Animation/StateMachine.h"
#include "Animation/AnimationState.h"
#include "Mocks/Animation/MockAnimator.h"

#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Animation;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestStateMachine)

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StateMachine_IsRegisteredWithComponentRegistry)
  {
    Assert::IsTrue(ComponentRegistry::hasComponent<StateMachine>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StateMachine_IsAllocatableFromComponentRegistry)
  {
    GameObject gameObject;

    observer_ptr<Component> component = ComponentRegistry::createComponent(StateMachine::type_name(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<StateMachine*>(component));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StateMachine_Constructor_SetsCurrentAnimationStateToNullptr)
  {
    GameObject gameObject;
    StateMachine stateMachine(gameObject);

    Assert::IsNull(stateMachine.getCurrentAnimationState());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StateMachine_Constructor_SetsTransitionsToEmpty)
  {
    GameObject gameObject;
    StateMachine stateMachine(gameObject);

    Assert::IsTrue(stateMachine.getStates().empty());
  }

#pragma endregion

#pragma region Set Starting State Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StateMachine_SetStartingState_ValidAnimationState_UpdatesStateMachineStartingState)
  {
    GameObject gameObject;
    StateMachine stateMachine(gameObject);
    Animator animator(gameObject);
    AnimationState animationState(animator);

    stateMachine.setStartingState(animationState);

    Assert::IsTrue(&animationState == stateMachine.getCurrentAnimationState());
  }

#pragma endregion

#pragma region Add States Single Input Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StateMachine_AddStates_WithValidAnimation_AddsAnimationState)
  {
    GameObject gameObject;
    StateMachine stateMachine(gameObject);
    Animator animator(gameObject);

    stateMachine.addStates(animator);

    Assert::AreEqual((size_t)1, stateMachine.getStates().size());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StateMachine_AddStates_WithNoPreviousStates_SetStateToStartingState)
  {
    GameObject gameObject;
    StateMachine stateMachine(gameObject);
    Animator animator(gameObject);

    Assert::IsNull(stateMachine.getCurrentAnimationState());

    stateMachine.addStates(animator);

    Assert::IsTrue(stateMachine.getCurrentAnimationState() == &stateMachine.getStates()[0]);
  }

#pragma endregion

#pragma region Add States Multiple Input Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StateMachine_AddStates_InputtingMultipleAnimators_AddsStatesForAll)
  {
    GameObject gameObject;
    StateMachine stateMachine(gameObject);
    Animator animator(gameObject);
    AnimationState animState1(animator);
    AnimationState animState2(animator);

    stateMachine.addStates(animState1, animState2);

    Assert::AreEqual((size_t)2, stateMachine.getStates().size());
  }

#pragma endregion

#pragma region Update Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StateMachine_Update_WithNoCurrentAnimationState_DoesNotThrow)
  {
    GameObject gameObject;
    StateMachine stateMachine(gameObject);

    Assert::IsNull(stateMachine.getCurrentAnimationState());

    // Check doesn't throw
    stateMachine.update(0);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StateMachine_Update_WithAnimationStates_TransitionsToFirstStateWhereTransitionFuncPasses)
  {
    GameObject gameObject;
    StateMachine stateMachine(gameObject);
    MockAnimator animator(gameObject);
    AnimationState animState1(animator);
    AnimationState animState2(animator);

    stateMachine.addStates(animState1, animState2);
    animState1.addTransition(animState2, []() -> bool { return true; });
    animState2.addTransition(animState1, []() -> bool { return false; });

    stateMachine.update(0);

    Assert::IsTrue(&animState2 == stateMachine.getCurrentAnimationState());

    stateMachine.update(0);

    // Should stay on anim state 2 as no valid transitions
    Assert::IsTrue(&animState2 == stateMachine.getCurrentAnimationState());
  }

#pragma endregion

  };
}