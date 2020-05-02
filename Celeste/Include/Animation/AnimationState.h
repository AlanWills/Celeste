#pragma once

#include "CelesteDllExport.h"
#include "CelesteStl/Memory/ObserverPtr.h"

#include <functional>
#include <unordered_map>


namespace Celeste::Animation
{
  class Animator;

  class AnimationState
  {
    public:
      using TransitionFunc = std::function<bool()>;
      using Transitions = std::unordered_map<observer_ptr<AnimationState>, TransitionFunc>;
      using Transition = std::pair<observer_ptr<AnimationState>, TransitionFunc>;
      
      CelesteDllExport AnimationState(Animator& animator);

      /// \brief Create a new transition between the two inputted animation states
      /// The inputted function dicatates when the 'from' state should move to the 'to' state
      CelesteDllExport void addTransition(
        AnimationState& to,
        const TransitionFunc& transitionFunc);

      /// \brief Resumes and restarts the animation
      CelesteDllExport void startAnimation();

      /// \brief Pauses and restarts the animation
      CelesteDllExport void stopAnimation();

      inline Transitions::const_iterator begin() const { return m_transitions.begin(); }
      inline Transitions::const_iterator end() const { return m_transitions.end(); }

      inline const Transitions& getTransitions() { return m_transitions; }

    private:
      Transitions m_transitions;
      Animator& m_animator;
  };
}