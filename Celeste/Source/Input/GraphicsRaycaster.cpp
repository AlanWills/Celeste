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
    Inherited(gameObject)
  {
  }

  //------------------------------------------------------------------------------------------------
  std::vector<observer_ptr<GameObject>> GraphicsRaycaster::raycast()
  {
    std::vector<observer_ptr<GameObject>> hitGameObjects;

    Ray ray = Ray(Input::getMouse().getTransform().getWorldTranslation(), glm::vec3(0, 0, -1));

    if (getGameObject().isActive())
    {
      m_gameObjectQueue.push_back(&getGameObject());
    }

    while (!m_gameObjectQueue.empty())
    {
      observer_ptr<GameObject> gameObject = m_gameObjectQueue.front();
      m_gameObjectQueue.pop_front();

      // Raycast the current game object renderer we are iterating on
      observer_ptr<Renderer> renderer = gameObject->findComponent<Renderer>();
      if (renderer != nullptr && renderer->isActive())
      {
        Maths::Rectangle rect;
        glm::vec2 scissorRectangleDims = renderer->getScissorRectangle().getDimensions();

        if (scissorRectangleDims == glm::zero<glm::vec2>())
        {
          rect.setCentre(gameObject->getTransform()->getWorldTranslation());
          rect.setDimensions(renderer->getScaledDimensions());
        }
        else
        {
          rect.setCentre(glm::vec2(gameObject->getTransform()->getWorldTranslation()) + renderer->getScissorRectangle().getCentre());
          rect.setDimensions(scissorRectangleDims * glm::vec2(gameObject->getTransform()->getScale()));
        }

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
          m_gameObjectQueue.push_back(child);
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