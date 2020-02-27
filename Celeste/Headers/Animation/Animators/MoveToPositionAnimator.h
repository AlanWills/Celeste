#pragma once

#include "Objects/Script.h"
#include "glm/glm.hpp"


namespace Celeste::Animators
{
  class MoveToPositionAnimator : public Script
  {
    DECLARE_SCRIPT(MoveToPositionAnimator, CelesteDllExport)

    public:
      inline float getTime() const { return m_time; }
      inline void setTime(float time) { m_time = time; }

      inline const glm::vec3& getTargetPosition() const { return m_targetPosition; }
      CelesteDllExport void setTargetPosition(const glm::vec3& targetPosition);

      CelesteDllExport void update(float elapsedGameTime) override;

    private:
      using Inherited = Script;

      void reset();

      float m_time;
      float m_elapsedTime;
      glm::vec3 m_targetPosition;
      glm::vec3 m_startingPosition;
  };
}