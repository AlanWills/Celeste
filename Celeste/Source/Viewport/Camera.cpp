#include "Viewport/Camera.h"
#include "Input/InputUtils.h"
#include "Input/Mouse.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  Camera::Camera() :
    m_transform(),
    m_projectionMode(ProjectionMode::kPerspective),
    m_nearPlane(0.1f),
    m_farPlane(100),
    m_viewportDimensions(1)
  {
    getTransform().setTranslation(glm::vec3(0, 0, 1));
  }

  //------------------------------------------------------------------------------------------------
  glm::mat4 Camera::getProjectionMatrix() const
  {
    return m_projectionMode == ProjectionMode::kPerspective ? getPerspectiveProjectionMatrix() : getOrthographicProjectionMatrix();
  }

  //------------------------------------------------------------------------------------------------
  glm::mat4 Camera::getPerspectiveProjectionMatrix() const
  {
    return glm::perspectiveFov<float>(45.0f, m_viewportDimensions.x, m_viewportDimensions.y, m_nearPlane, m_farPlane);
  }

  //------------------------------------------------------------------------------------------------
  glm::mat4 Camera::getOrthographicProjectionMatrix() const
  {
    return glm::ortho<float>(0, m_viewportDimensions.x, 0, m_viewportDimensions.y);
  }

  //------------------------------------------------------------------------------------------------
  glm::mat4 Camera::getViewMatrix() const
  {
    // If we are rendering in orthographic, return the identity
    return m_projectionMode == ProjectionMode::kOrthographic ? glm::mat4() : glm::translate(glm::mat4(), -getTransform().getTranslation());
  }

  //------------------------------------------------------------------------------------------------
  Maths::Ray Camera::createRay() const
  { 
    return createRay(glm::vec2(Input::getMouse().getTransform().getWorldTranslation()));
  }

  //------------------------------------------------------------------------------------------------
  Maths::Ray Camera::createRay(const glm::vec2& screenPosition) const
  {
    // Orthographic specific ray stuff
    if (m_projectionMode == ProjectionMode::kOrthographic)
    {
      return Maths::Ray(glm::vec3(screenPosition, 0) + getTransform().getWorldTranslation(), glm::vec3(0, 0, -1));
    }
    else if (m_projectionMode == ProjectionMode::kPerspective)
    {
      // Perspective ray creation
      Maths::Ray ray;
      ray.m_origin = getTransform().getTranslation();

      float mouseX = screenPosition.x / (m_viewportDimensions.x  * 0.5f) - 1.0f;
      float mouseY = screenPosition.y / (m_viewportDimensions.y * 0.5f) - 1.0f;

      glm::mat4 invP = glm::inverse(getPerspectiveProjectionMatrix());
      glm::vec4 clipSpace = glm::vec4(mouseX, mouseY, -1, 1);
      glm::vec4 eyeSpace = invP * clipSpace;
      eyeSpace.z = -1;
      eyeSpace.w = 0;
      glm::mat4 invV = glm::inverse(getViewMatrix());
      glm::vec4 worldPos = invV * eyeSpace;

      ray.m_direction = glm::normalize(glm::vec3(worldPos));

      return ray;
    }
    
    ASSERT_FAIL();
    return Maths::Ray();
  }
}