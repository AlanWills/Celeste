#pragma once

#include "Objects/Component.h"
#include "glm/glm.hpp"


namespace Celeste::Animators
{
  class MoveToPositionAnimator : public Component
  {
    DECLARE_UNMANAGED_COMPONENT(MoveToPositionAnimator, CelesteDllExport)

    public:
      inline float getTime() const { return m_time; }
      inline void setTime(float time) { m_time = time; }

      inline const glm::vec3& getTargetPosition() const { return m_targetPosition; }
      CelesteDllExport void setTargetPosition(const glm::vec3& targetPosition);

      CelesteDllExport void update() override;

    private:
      using Inherited = Component;

      void reset();

      float m_time;
      float m_elapsedTime;
      glm::vec3 m_targetPosition;
      glm::vec3 m_startingPosition;
  };
}