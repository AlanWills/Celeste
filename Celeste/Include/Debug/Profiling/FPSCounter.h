#pragma once

#include "CelesteDllExport.h"
#include "Objects/Component.h"


namespace Celeste::Rendering
{
  class TextRenderer;
}

namespace Celeste::Debugging
{
  class FPSCounter : public Component
  {
    DECLARE_UNMANAGED_COMPONENT(FPSCounter, CelesteDllExport)

    public:
      CelesteDllExport void update() override;

    private:
      using Inherited = Celeste::Component;

      observer_ptr<Celeste::Rendering::TextRenderer> m_textRenderer;
      float m_current;
  };
}