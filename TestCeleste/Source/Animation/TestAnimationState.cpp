#include "UtilityHeaders/UnitTestHeaders.h"
#include "Animation/AnimationState.h"
#include "Mocks/Animation/MockAnimator.h"
#include "Registries/ComponentRegistry.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Animation;


namespace TestCeleste::Animation
{
  CELESTE_TEST_CLASS(TestAnimationState)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimationState_Constructor_SetsValuesToDefault)
  {
    Animator animator;
    AnimationState animState(animator);

    Assert::IsTrue(animState.getTransitions().empty());
  }

#pragma endregion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimationState_StartAnimation_ResetsAndPlaysAnimation)
  {
    MockAnimator animation;
    AnimationState animState(animation);

    animation.setCurrentSecondsPerFrame_Public(1);
    animation.setCurrentFrame_Public(1);
    animation.setPlaying_Public(false);

    animState.startAnimation();

    Assert::AreEqual(0.0f, animation.getCurrentSecondsPerFrame_Public());
    Assert::AreEqual((size_t)0, animation.getCurrentFrame_Public());
    Assert::IsTrue(animation.isPlaying());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimationState_StopAnimation_ResetsAndStopsAnimation)
  {
    MockAnimator animation;
    AnimationState animState(animation);

    animation.setCurrentSecondsPerFrame_Public(1);
    animation.setCurrentFrame_Public(1);
    animation.setPlaying_Public(true);

    animState.stopAnimation();

    Assert::AreEqual(0.0f, animation.getCurrentSecondsPerFrame_Public());
    Assert::AreEqual((size_t)0, animation.getCurrentFrame_Public());
    Assert::IsFalse(animation.isPlaying());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimationState_AddTransitionToSelf_DoesNotAddTransition)
  {
    MockAnimator animator;
    AnimationState animState1(animator);

    animState1.addTransition(animState1, []() -> bool { return false; });

    Assert::IsTrue(animState1.getTransitions().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AnimationState_AddTransitionToAnotherState_AddsTransition)
  {
    MockAnimator animator;
    AnimationState animState1(animator);
    AnimationState animState2(animator);

    animState1.addTransition(animState2, []() -> bool { return false; });

    Assert::IsFalse(animState1.getTransitions().empty());
  }

  };
}