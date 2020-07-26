#pragma once

#include "CelesteDllExport.h"
#include "System/ISystem.h"
#include "glm/glm.hpp"
#include "Events/EventHandle.h"

#include <vector>


namespace Celeste
{
  class OpenGLWindow;
}

namespace Celeste::Layout
{
  class LayoutSystem : public System::ISystem
  {
    public:
      CelesteDllExport LayoutSystem(OpenGLWindow& glWindow);
      CelesteDllExport ~LayoutSystem();

      CelesteDllExport void update(float elapsedGameTime) override;

    private:
      void rescaleAll(const glm::vec2& newContentArea);

      OpenGLWindow& m_glWindow;
      EventHandle m_resolutionChangedHandle = EventHandle();
      glm::vec2 m_lastAppliedContentArea;
  };
}