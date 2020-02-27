#pragma once

#include "Objects/Script.h"
#include "glm/glm.hpp"


namespace Celeste::Animators
{
  class ChangeScaleAnimator : public Script
  {
    DECLARE_SCRIPT(ChangeScaleAnimator, CelesteDllExport)

    public:
      inline float getTime() const { return m_time; }
      inline void setTime(float time) { m_time = time; }

      inline const glm::vec3& getTargetScale() const { return m_targetScale; }
      CelesteDllExport void setTargetScale(const glm::vec3& targetScale);

      void update(float elapsedGameTime) override;

    private:
      using Inherited = Script;

      void reset();

      float m_time;
      float m_elapsedTime;
      glm::vec3 m_startingScale;
      glm::vec3 m_targetScale;
  };
}