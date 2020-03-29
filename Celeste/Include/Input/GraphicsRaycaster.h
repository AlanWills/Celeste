#pragma once

#include "Objects/Component.h"

#include <deque>


namespace Celeste
{
  class GameObject;
}

namespace Celeste::Rendering
{
  class Canvas;
}

namespace Celeste::Input
{
  class GraphicsRaycaster : public Component
  {
    DECLARE_MANAGED_COMPONENT(GraphicsRaycaster, InputManager, CelesteDllExport);

    public:
      CelesteDllExport std::vector<observer_ptr<GameObject>> raycast();

    private:
      using Inherited = Component;

      std::deque<observer_ptr<GameObject>> m_gameObjectQueue;
  };
}