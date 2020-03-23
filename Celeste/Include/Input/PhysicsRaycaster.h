#pragma once

#include "Objects/Component.h"


namespace Celeste::Rendering
{
  class Canvas;
}

namespace Celeste::Input
{
  class PhysicsRaycaster : public Component
  {
    DECLARE_MANAGED_COMPONENT(PhysicsRaycaster, InputManager, CelesteDllExport);

    public:
      std::vector<observer_ptr<GameObject>> raycast() const;

    private:
      using Inherited = Component;

      observer_ptr<Rendering::Canvas> m_canvas;
  };
}