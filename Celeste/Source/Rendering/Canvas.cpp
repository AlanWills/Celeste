#include "Rendering/Canvas.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Scene/SceneUtils.h"
#include "Rendering/Renderer.h"
#include "Viewport/OpenGLWindow.h"


namespace Celeste::Rendering
{
  REGISTER_COMPONENT(Canvas, 10)

  //------------------------------------------------------------------------------------------------
  Canvas::Canvas(GameObject& gameObject) :
    Inherited(gameObject),
    m_spriteBatch(),
    m_gameObjectQueue()
  {
    m_spriteBatch.initialize();
  }

  //------------------------------------------------------------------------------------------------
  void Canvas::render(float lag)
  {
    glm::vec2 viewportDimensions = getWindow().getContentArea();
    m_spriteBatch.begin(glm::ortho<float>(0, viewportDimensions.x, 0, viewportDimensions.y), glm::identity<glm::mat4>());

    // Breadth first walk this game object and it's children to find all game objects 
    // that need rendering by this canvas

    ASSERT(m_gameObjectQueue.empty());

    if (GameObject& gameObject = getGameObject(); gameObject.isActive())
    {
      m_gameObjectQueue.push_back(&gameObject);
    }

    while (!m_gameObjectQueue.empty())
    {
      observer_ptr<GameObject> gameObject = m_gameObjectQueue.front();
      m_gameObjectQueue.pop_front();

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
            m_gameObjectQueue.push_back(child);
          }
        }
      }
    }

    m_spriteBatch.end();
  }
}