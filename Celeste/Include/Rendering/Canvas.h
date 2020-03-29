#pragma once

#include "Objects/Component.h"
#include "Rendering/SpriteBatch.h"

#include <deque>


namespace Celeste
{
  class Camera;

  namespace Rendering
  {
    class Canvas : public Component
    {
      DECLARE_MANAGED_COMPONENT(Canvas, RenderManager, CelesteDllExport)

      public:
        CelesteDllExport void render(float lag);
      
        // In the future we can update this when we need it, to use a camera for camera space
        // rendering or world space rendering, but for now this is good enough
        // If this happens, we'll need to update the raycasters too

      private:
        using Inherited = Component;

        SpriteBatch m_spriteBatch;

        std::deque<observer_ptr<GameObject>> m_gameObjectQueue;
    };
  }
}