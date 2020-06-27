#pragma once

#include "Objects/Component.h"
#include "glm/glm.hpp"


namespace Celeste::Layout
{
  class LayoutSystem;

  class ResolutionScaler : public Component
  {
    DECLARE_MANAGED_COMPONENT(ResolutionScaler, LayoutSystem, CelesteDllExport);

    public:
      bool needsRescale() const { return m_needsRescale; }
      void markForRescale() { m_needsRescale = true; }

      void rescale(const glm::vec2& oldResolution, const glm::vec2& newResolution);

      const glm::vec2& getTargetResolution() const { return m_targetResolution; }
      CelesteDllExport void setTargetResolution(const glm::vec2& targetResolution);

    private:
      using Inherited = Component;

      glm::vec2 m_targetResolution;
      bool m_needsRescale = true;
  };
}