#pragma once

#include "CelesteDllExport.h"
#include "System/ISystem.h"
#include "UID/StringId.h"
#include "glm/glm.hpp"

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
      CelesteDllExport LayoutSystem(const OpenGLWindow& glWindow);
      CelesteDllExport ~LayoutSystem();

      CelesteDllExport void update(float elapsedGameTime) override;

    private:
      void rescaleAll(const glm::vec2& newContentArea);

      const OpenGLWindow& m_glWindow;
      StringId m_resolutionChangedHandle = StringId();
      glm::vec2 m_lastAppliedContentArea;
  };
}