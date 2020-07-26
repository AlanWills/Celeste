#pragma once

#include "Objects/Component.h"
#include "Maths/Ray.h"
#include "Viewport/ViewportEnums.h"


namespace Celeste
{
  class Camera : public Component
  {
    DECLARE_UNMANAGED_COMPONENT(Camera, CelesteDllExport);

    public:
      CelesteDllExport glm::mat4 getProjectionMatrix() const;
      CelesteDllExport glm::mat4 getViewMatrix() const;

      CelesteDllExport Maths::Ray createRay() const;
      CelesteDllExport Maths::Ray createRay(const glm::vec2& screenPosition) const;

      inline void setProjectionMode(ProjectionMode mode) { m_projectionMode = mode; }
      inline ProjectionMode getProjectionMode() const { return m_projectionMode; }

      inline float getAspectRatio() const { return m_viewportDimensions.x / m_viewportDimensions.y; }

      inline float getNearPlane() const { return m_nearPlane; }
      inline void setNearPlane(float nearPlane) { m_nearPlane = nearPlane; }

      inline float getFarPlane() const { return m_farPlane; }
      inline void setFarPlane(float farPlane) { m_farPlane = farPlane; }

      inline const glm::vec2& getViewportDimensions() const { return m_viewportDimensions; }
      inline void setViewportDimensions(float width, float height) { setViewportDimensions(glm::vec2(width, height)); }
      inline void setViewportDimensions(const glm::vec2& viewportDimensions)
      { 
        ASSERT(viewportDimensions.y != 0);
        m_viewportDimensions = viewportDimensions; 
      }

    private:
      using Inherited = Component;

      glm::mat4 getPerspectiveProjectionMatrix() const;
      glm::mat4 getOrthographicProjectionMatrix() const;

      ProjectionMode m_projectionMode;
      float m_nearPlane;
      float m_farPlane;
      glm::vec2 m_viewportDimensions;
  };
}