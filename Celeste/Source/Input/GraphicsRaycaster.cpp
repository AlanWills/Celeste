#include "Input/GraphicsRaycaster.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Rendering/Canvas.h"
#include "Rendering/Renderer.h"
#include "Input/InputUtils.h"
#include "Input/Mouse.h"
#include "Maths/Rectangle.h"
#include "Maths/Ray.h"

using namespace Celeste::Maths;
using namespace Celeste::Rendering;


namespace Celeste::Input
{
  REGISTER_COMPONENT(GraphicsRaycaster, 10);

  //------------------------------------------------------------------------------------------------
  GraphicsRaycaster::GraphicsRaycaster(GameObject& gameObject) :
    Inherited(gameObject),
    m_canvas(gameObject.findComponent<Rendering::Canvas>())
  {
    ASSERT(m_canvas);
  }

  //------------------------------------------------------------------------------------------------
  std::vector<observer_ptr<GameObject>> GraphicsRaycaster::raycast() const
  {
    std::queue<observer_ptr<GameObject>> gameObjectQueue;
    std::vector<observer_ptr<GameObject>> hitGameObjects;

    Ray ray = Ray(glm::vec3(Input::getMouse().getScreenPosition(), 0), glm::vec3(0, 0, -1));
    observer_ptr<GameObject> canvasGameObject = m_canvas->getGameObject();

    if (canvasGameObject->isActive())
    {
      gameObjectQueue.push(canvasGameObject);
    }

    while (!gameObjectQueue.empty())
    {
      observer_ptr<GameObject> gameObject = gameObjectQueue.front();
      gameObjectQueue.pop();

      // Do another check here because sibling elements could have changed the activation status in their collision calls
      if (gameObject->isActive())
      {
        // Raycast the current game object renderer we are iterating on
        observer_ptr<Renderer> renderer = gameObject->findComponent<Renderer>();
        if (renderer != nullptr && renderer->isActive())
        {
          Maths::Rectangle rect(gameObject->getTransform()->getWorldTranslation(), renderer->getScaledDimensions());

          if (rect.contains(ray.m_origin))
          {
            hitGameObjects.push_back(gameObject);
          }
        }

        // Go through each child
        for (observer_ptr<GameObject> child : *gameObject)
        {
          if (child->isActive() && !child->hasComponent<Canvas>())
          {
            // If we have a child which should be raycasted and it does not have a Canvas
            // it should be included in the raycast process for this Canvas
            gameObjectQueue.push(child);
          }
        }
      }
    }
    
    // Sort into descending z order
    std::sort(hitGameObjects.begin(), hitGameObjects.end(), [](observer_ptr<GameObject> lhs, observer_ptr<GameObject> rhs) -> bool
      {
        return lhs->getTransform()->getWorldTranslation().z > rhs->getTransform()->getWorldTranslation().z;
      });
    return hitGameObjects;
  }
}