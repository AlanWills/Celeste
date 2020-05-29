#include "Animation/StateMachine.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace Celeste::Animation
{
  REGISTER_COMPONENT(StateMachine, 10)

  //------------------------------------------------------------------------------------------------
  StateMachine::StateMachine(GameObject& gameObject) :
    Inherited(gameObject),
    m_currentAnimStateIndex(0)
  {
  }

  //------------------------------------------------------------------------------------------------
  void StateMachine::update()
  {
    Inherited::update();

#if _DEBUG
    if (m_currentAnimStateIndex >= m_states.size())
    {
      ASSERT_FAIL();
      return;
    }
#endif

    AnimationState& animState = m_states[m_currentAnimStateIndex];

    for (const AnimationState::Transition& transition : animState)
    {
      if (transition.second())
      {
        // Stop this current animation from playing and reset it back to it's beginning
        animState.stopAnimation();

        // Now update the current animation state to the destination state of the transition and play it
        setStartingState(*transition.first);
        animState.startAnimation();

        // Currently we transition on the first one that passes
        break;
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void StateMachine::setStartingState(const AnimationState& /*animationState*/)
  {
    /*for (size_t i = 0; i < m_states.size(); ++i)
    {
      if (animationState ==)
    }*/
  }

  //------------------------------------------------------------------------------------------------
  void StateMachine::addStates(const AnimationState& animationState)
  {
    bool isFirst = m_states.empty();
    m_states.push_back(animationState);

    if (isFirst)
    {
      // If this is the first state we have added, automatically make it the starting state
      setStartingState(m_states.back());
    }
  }
}