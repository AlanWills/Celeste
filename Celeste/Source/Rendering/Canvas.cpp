#include "Rendering/Canvas.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Viewport/Camera.h"
#include "Screens/ScreenUtils.h"
#include "Screens/Screen.h"
#include "Physics/Collider.h"
#include "Rendering/Renderer.h"

#include <stack>


namespace Celeste::Rendering
{
  REGISTER_COMPONENT(Canvas, 10)

  //------------------------------------------------------------------------------------------------
  Canvas::Canvas() :
    m_spriteBatch(),
    m_camera(),
    m_gameObjectQueue()
  {
    m_spriteBatch.initialize();
    m_camera.setViewportDimensions(getViewportDimensions());
  }

  //------------------------------------------------------------------------------------------------
  void Canvas::onHandleInput()
  {
    Inherited::onHandleInput();

    Maths::Ray ray = m_camera.createRay();

    ASSERT(m_gameObjectQueue.empty());

    observer_ptr<GameObject> thisGameObject = getGameObject();
    if (thisGameObject->isActive())
    {
      m_gameObjectQueue.push(thisGameObject);
    }

    float currentNearest = -std::numeric_limits<float>::max();
    observer_ptr<Physics::Collider> nearestCollider = nullptr;

    while (!m_gameObjectQueue.empty())
    {
      observer_ptr<GameObject> gameObject = m_gameObjectQueue.front();
      m_gameObjectQueue.pop();

      // Do another check here because sibling elements could have changed the activation status in their collision calls
      if (gameObject->isActive())
      {
        // Raycast the current game object collider we are iterating on
        observer_ptr<Physics::Collider> collider = gameObject->findComponent<Physics::Collider>();
        if (collider != nullptr && collider->isActive())
        {
          collider->setHitByRay(false);

          float worldZ = gameObject->getTransform()->getWorldTranslation().z;
          if (worldZ >= currentNearest && collider->intersects(ray))
          {
            currentNearest = worldZ;
            nearestCollider = collider;
          }
        }

        // Go through each child
        for (observer_ptr<GameObject> child : *gameObject)
        {
          if (child->isActive() && !child->hasComponent<Canvas>())
          {
            // If we have a child which should be raycasted and it does not have a Canvas
            // it should be included in the raycast process for this Canvas
            m_gameObjectQueue.push(child);
          }
        }
      }
    }

    if (nearestCollider != nullptr)
    {
      nearestCollider->setHitByRay(true);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Canvas::onDeath()
  {
    Inherited::onDeath();

    m_spriteBatch.destroy();
    m_camera = Camera();

    // Nothing in the handle input or render functions interrupts so this should always be empty if it's ever killed
    ASSERT(m_gameObjectQueue.empty());
  }

  //------------------------------------------------------------------------------------------------
  void Canvas::render(float lag)
  {
    m_spriteBatch.begin(m_camera.getProjectionMatrix(), m_camera.getViewMatrix());

    // Breadth first walk this game object and it's children to find all game objects 
    // that need rendering by this canvas

    ASSERT(m_gameObjectQueue.empty());

    if (observer_ptr<GameObject> gameObject = getGameObject(); gameObject->isActive())
    {
      m_gameObjectQueue.push(gameObject);
    }

    while (!m_gameObjectQueue.empty())
    {
      observer_ptr<GameObject> gameObject = m_gameObjectQueue.front();
      m_gameObjectQueue.pop();

      // Do another check here because sibling elements could have changed the render status in their render call
      if (gameObject->isActive())
      {
        if (observer_ptr<Renderer> renderer = gameObject->findComponent<Renderer>(); renderer != nullptr && renderer->isActive())
        {
          // Render the current game object we are iterating on
          gameObject->render(m_spriteBatch, lag);
        }

        // Go through each child
        for (observer_ptr<GameObject> child : *gameObject)
        {
          if (child->isActive() && !child->hasComponent<Canvas>())
          {
            // If we have a child which should be rendered and it does not have a Canvas
            // it should be included in the render process for this Canvas
            m_gameObjectQueue.push(child);
          }
        }
      }
    }

    m_spriteBatch.end();
  }

  //------------------------------------------------------------------------------------------------
  void Canvas::setDimensions(const glm::vec2& canvasDimensions)
  {
    m_camera.setViewportDimensions(canvasDimensions);

    if (m_camera.getProjectionMode() == ProjectionMode::kPerspective)
    {
      // Scale so that a game unit is half the screen
      m_camera.getTransform().setScale(2 / canvasDimensions.x, 2 / canvasDimensions.x);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Canvas::setProjectionMode(ProjectionMode projectionMode)
  {
    if (m_camera.getProjectionMode() == projectionMode)
    {
      return;
    }

    m_camera.setProjectionMode(projectionMode);

    if (projectionMode == ProjectionMode::kOrthographic)
    {
      // To avoid going out of the near/far plane for the camera rendering
      m_camera.getTransform().setTranslation(0, 0, 0.1f);
      m_camera.getTransform().setScale(1, 1, 1);
    }
    else
    {
      m_camera.getTransform().setTranslation(0, 0, 0);

      // Scale so that a game unit is half the screen
      // Not a typo - we cannot scale by both x and y otherwise the world would be distorted
      m_camera.getTransform().setScale(2 / m_camera.getViewportDimensions().x, 2 / m_camera.getViewportDimensions().x);
    }
  }
}