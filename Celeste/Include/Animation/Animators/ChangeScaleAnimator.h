#pragma once

#include "Objects/Component.h"
#include "glm/glm.hpp"


namespace Celeste::Animators
{
  class ChangeScaleAnimator : public Component
  {
    DECLARE_UNMANAGED_COMPONENT(ChangeScaleAnimator, CelesteDllExport)

    public:
      inline float getTime() const { return m_time; }
      inline void setTime(float time) { m_time = time; }

      inline const glm::vec3& getTargetScale() const { return m_targetScale; }
      CelesteDllExport void setTargetScale(const glm::vec3& targetScale);

      CelesteDllExport void update() override;

    private:
      using Inherited = Component;

      void reset();

      float m_time;
      float m_elapsedTime;
      glm::vec3 m_startingScale;
      glm::vec3 m_targetScale;
  };
}