#pragma once

#include "Objects/Script.h"
#include "AnimationState.h"


namespace Celeste::Animation
{
  class StateMachine : public Script
  {
    DECLARE_SCRIPT(StateMachine, CelesteDllExport)

    protected:
      using States = std::vector<AnimationState>;

    public:
      template <typename ...Args>
      void addStates(const AnimationState& animationState, const Args&... animationStates);
      CelesteDllExport void addStates(const AnimationState& animator);

      /// \brief Sets the current animstate to the inputted one
      /// This can only occur before awake() is called - from then on, the state machine has full control
      CelesteDllExport void setStartingState(const AnimationState& animState);

      inline observer_ptr<const AnimationState> getCurrentAnimationState() const { return &m_states[m_currentAnimStateIndex]; }
      inline const States& getStates() const { return m_states; }

      CelesteDllExport void update(float secondsPerUpdate) override;

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