#pragma once

#include "CelesteDllExport.h"
#include "Objects/Script.h"


namespace Celeste::Rendering
{
  class SpriteRenderer;
}

namespace Celeste::UI
{
  class ProgressBar : public Script
  {
    DECLARE_SCRIPT(ProgressBar, CelesteDllExport)

    public:
      inline float getMin() const { return m_min; }
      CelesteDllExport void setMin(float min);

      inline float getMax() const { return m_max; }
      CelesteDllExport void setMax(float max);

      inline float getProgress() const { return m_progress; }
      CelesteDllExport void setProgress(float progress);

    protected:
      CelesteDllExport void onSetGameObject(GameObject& gameObject) override;
      CelesteDllExport void onDeath() override;

    private:
      using Inherited = Script;

      observer_ptr<Rendering::SpriteRenderer> m_spriteRenderer;

      float m_progress;
      float m_min;
      float m_max;
  };
}