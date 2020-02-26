#include "Animation/AnimationState.h"
#include "Animation/Animator.h"
#include "Debug/Assert.h"


namespace Celeste::Animation
{
  //------------------------------------------------------------------------------------------------
  AnimationState::AnimationState(Animator& animator) :
    m_animator(animator)
  {
  }

  //------------------------------------------------------------------------------------------------
  void AnimationState::addTransition(
    AnimationState& to,
    const TransitionFunc& transitionFunc)
  {
    if (this == &to)
    {
      // Cannot have a self transition
      ASSERT_FAIL();
      return;
    }

    // Add the transition to the map
    m_transitions.emplace(&to, transitionFunc);
  }

  //------------------------------------------------------------------------------------------------
  void AnimationState::startAnimation()
  {
    // This resets the sprite renderer's texture for the parent
    m_animator.restart();
    m_animator.play();
  }

  //------------------------------------------------------------------------------------------------
  void AnimationState::stopAnimation()
  {
    m_animator.pause();
    m_animator.restart();
  }
}