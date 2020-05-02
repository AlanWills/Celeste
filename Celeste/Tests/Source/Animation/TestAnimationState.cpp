#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"
#include "Animation/AnimationState.h"
#include "Mocks/Animation/MockAnimator.h"
#include "Registries/ComponentRegistry.h"
#include "TestUtils/Assert/AssertCel.h"

using namespace Celeste;
using namespace Celeste::Animation;


namespace TestCeleste::Animation
{
  CELESTE_TEST_CLASS(TestAnimationState)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimationState_Constructor_SetsValuesToDefault)
  {
    GameObject gameObject;
    Animator animator(gameObject);
    AnimationState animState(animator);

    Assert::IsTrue(animState.getTransitions().empty());
  }

#pragma endregion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimationState_StartAnimation_ResetsAndPlaysAnimation)
  {
    GameObject gameObject;
    MockAnimator animator(gameObject);
    AnimationState animState(animator);

    animator.setCurrentSecondsPerFrame_Public(1);
    animator.setCurrentFrame_Public(1);
    animator.setPlaying_Public(false);

    animState.startAnimation();

    Assert::AreEqual(0.0f, animator.getCurrentSecondsPerFrame_Public());
    Assert::AreEqual((size_t)0, animator.getCurrentFrame_Public());
    Assert::IsTrue(animator.isPlaying());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimationState_StopAnimation_ResetsAndStopsAnimation)
  {
    GameObject gameObject;
    MockAnimator animator(gameObject);
    AnimationState animState(animator);

    animator.setCurrentSecondsPerFrame_Public(1);
    animator.setCurrentFrame_Public(1);
    animator.setPlaying_Public(true);

    animState.stopAnimation();

    Assert::AreEqual(0.0f, animator.getCurrentSecondsPerFrame_Public());
    Assert::AreEqual((size_t)0, animator.getCurrentFrame_Public());
    Assert::IsFalse(animator.isPlaying());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimationState_AddTransitionToSelf_DoesNotAddTransition)
  {
    GameObject gameObject;
    MockAnimator animator(gameObject);
    AnimationState animState1(animator);

    animState1.addTransition(animState1, []() -> bool { return false; });

    Assert::IsTrue(animState1.getTransitions().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimationState_AddTransitionToAnotherState_AddsTransition)
  {
    GameObject gameObject;
    MockAnimator animator(gameObject);
    AnimationState animState1(animator);
    AnimationState animState2(animator);

    animState1.addTransition(animState2, []() -> bool { return false; });

    Assert::IsFalse(animState1.getTransitions().empty());
  }

  };
}