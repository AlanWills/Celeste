#pragma once

#include "Objects/Component.h"
#include "AnimationState.h"


namespace Celeste::Animation
{
  class StateMachine : public Component
  {
    DECLARE_UNMANAGED_COMPONENT(StateMachine, CelesteDllExport)

    protected:
      using States = std::vector<AnimationState>;

    public:
      template <typename ...Args>
      void addStates(const AnimationState& animationState, const Args&... animationStates);
      CelesteDllExport void addStates(const AnimationState& animator);

      /// \brief Sets the current animstate to the inputted one
      /// This can only occur before awake() is called - from then on, the state machine has full control
      CelesteDllExport void setStartingState(const AnimationState& animState);

      inline observer_ptr<const AnimationState> getCurrentAnimationState() const 
      { 
        return m_currentAnimStateIndex < m_states.size() ? &m_states[m_currentAnimStateIndex] : nullptr; 
      }

      inline const States& getStates() const { return m_states; }

      CelesteDllExport void update() override;

    private:
      using Inherited = Component;

      size_t m_currentAnimStateIndex;
      States m_states;
  };

  //------------------------------------------------------------------------------------------------
  template <typename ...Args>
  void StateMachine::addStates(const AnimationState& animationState, const Args&... animationStates)
  {
    addStates(animationState);
    addStates(animationStates...);
  }
}