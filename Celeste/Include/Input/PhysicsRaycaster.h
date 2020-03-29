#pragma once

#include "Objects/Component.h"

#include <deque>


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
      CelesteDllExport std::vector<observer_ptr<GameObject>> raycast();

    private:
      using Inherited = Component;
  
      std::deque<observer_ptr<GameObject>> m_gameObjectQueue;
  };
}