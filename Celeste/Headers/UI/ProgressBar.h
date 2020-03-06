#pragma once

#include "CelesteDllExport.h"
#include "Objects/Component.h"


namespace Celeste::Rendering
{
  class SpriteRenderer;
}

namespace Celeste::UI
{
  class ProgressBar : public Component
  {
    DECLARE_UNMANAGED_COMPONENT(ProgressBar, CelesteDllExport)

    public:
      inline float getMin() const { return m_min; }
      CelesteDllExport void setMin(float min);

      inline float getMax() const { return m_max; }
      CelesteDllExport void setMax(float max);

      inline float getProgress() const { return m_progress; }
      CelesteDllExport void setProgress(float progress);

    private:
      using Inherited = Component;

      observer_ptr<Rendering::SpriteRenderer> m_spriteRenderer;

      float m_progress;
      float m_min;
      float m_max;
  };
}