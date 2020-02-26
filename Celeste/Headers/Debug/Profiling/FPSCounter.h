#pragma once

#include "CelesteDllExport.h"
#include "Objects/Script.h"


namespace Celeste::Rendering
{
  class TextRenderer;
}

namespace Celeste::Debugging
{
  class FPSCounter : public Script
  {
    DECLARE_SCRIPT(FPSCounter, CelesteDllExport)

    protected:
      CelesteDllExport void onSetGameObject(GameObject& gameObject) override;
      CelesteDllExport void onUpdate(float elapsedGameTime) override;

    private:
      using Inherited = Celeste::Script;

      observer_ptr<Celeste::Rendering::TextRenderer> m_textRenderer;
      float m_current;
  };
}