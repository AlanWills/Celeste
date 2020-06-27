#pragma once

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
      LayoutSystem(const OpenGLWindow& glWindow);
      ~LayoutSystem();

      void update(float elapsedGameTime) override;

    private:
      void rescaleAll(const glm::vec2& newResolution);

      const OpenGLWindow& m_glWindow;
      StringId m_viewportChangedHandle = StringId();
      glm::vec2 m_lastAppliedResolution;
  };
}