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

    public:
      CelesteDllExport void update(float elapsedGameTime) override;

    protected:
      CelesteDllExport void onSetGameObject(GameObject& gameObject) override;

    private:
      using Inherited = Celeste::Script;

      observer_ptr<Celeste::Rendering::TextRenderer> m_textRenderer;
      float m_current;
  };
}