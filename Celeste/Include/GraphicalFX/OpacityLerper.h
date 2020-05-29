#pragma once

#include "Objects/Component.h"


namespace Celeste
{
  namespace Rendering
  {
    class Renderer;
  }

  class OpacityLerper : public Component
  {
    DECLARE_UNMANAGED_COMPONENT(OpacityLerper, CelesteDllExport)

    public:
      inline float getMinOpacity() const { return m_minOpacity; }
      inline void setMinOpacity(float minOpacity) { m_minOpacity = minOpacity; }

      inline float getMaxOpacity() const { return m_maxOpacity; }
      inline void setMaxOpacity(float maxOpacity) { m_maxOpacity = maxOpacity; }

      inline float getLerpUpTime() const { return m_lerpUpTime; }
      inline void setLerpUpTime(float lerpUpTime) { m_lerpUpTime = lerpUpTime; }

      inline float getLerpDownTime() const { return m_lerpDownTime; }
      inline void setLerpDownTime(float lerpDownTime) { m_lerpDownTime = lerpDownTime; }

      inline float getMaxOpacityWaitTime() const { return m_maxOpacityWaitTime; }
      inline void setMaxOpacityWaitTime(float maxOpacityWaitTime) { m_maxOpacityWaitTime = maxOpacityWaitTime; }

      inline float getMinOpacityWaitTime() const { return m_minOpacityWaitTime; }
      inline void setMinOpacityWaitTime(float minOpacityWaitTime) { m_minOpacityWaitTime = minOpacityWaitTime; }

      inline bool isLerpingUp() const { return m_lerpingUp; }
      inline void setLerpingUp(bool lerpingUp) { m_lerpingUp = lerpingUp; }

      CelesteDllExport void update() override;

    private:
      using Inherited = Component;

      float m_minOpacity;
      float m_maxOpacity;
      float m_lerpUpTime;
      float m_lerpDownTime;
      float m_maxOpacityWaitTime;
      float m_minOpacityWaitTime;
      float m_waitTime;

      bool m_lerpingUp;
  };
}