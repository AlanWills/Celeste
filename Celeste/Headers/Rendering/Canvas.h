#pragma once

#include "Objects/Component.h"
#include "Rendering/SpriteBatch.h"
#include "Viewport/Camera.h"

#include <queue>


namespace Celeste
{
  class Camera;

  namespace Rendering
  {
    class Canvas : public Component
    {
      DECLARE_COMPONENT(Canvas, RenderManager, CelesteDllExport)

      public:
        const glm::vec2& getDimensions() const { return m_camera.getViewportDimensions(); }
        CelesteDllExport void setDimensions(const glm::vec2& canvasDimensions);
        void setDimensions(float canvasXDimension, float canvasYDimension) { setDimensions(glm::vec2(canvasXDimension, canvasYDimension)); }

        ProjectionMode getProjectionMode() const { return m_camera.getProjectionMode(); }
        CelesteDllExport void setProjectionMode(ProjectionMode projectionMode);

        CelesteDllExport void render(float lag);

      protected:
        CelesteDllExport void onHandleInput() override;
        CelesteDllExport void onDeath() override;
      
      private:
        using Inherited = Component;

        SpriteBatch m_spriteBatch;
        Camera m_camera;

        std::queue<observer_ptr<GameObject>> m_gameObjectQueue;
    };
  }
}