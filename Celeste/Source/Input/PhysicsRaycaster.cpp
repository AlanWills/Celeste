#include "Input/PhysicsRaycaster.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Rendering/Canvas.h"
#include "Physics/Collider.h"
#include "Input/InputUtils.h"
#include "Input/Mouse.h"
#include "Maths/Ray.h"

using namespace Celeste::Maths;
using namespace Celeste::Physics;


namespace Celeste::Input
{
  REGISTER_COMPONENT(PhysicsRaycaster, 10);

  //------------------------------------------------------------------------------------------------
  PhysicsRaycaster::PhysicsRaycaster(GameObject& gameObject) :
    Inherited(gameObject)
  {
  }

  //------------------------------------------------------------------------------------------------
  std::vector<observer_ptr<GameObject>> PhysicsRaycaster::raycast()
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

      // Raycast the current game object collider we are iterating on
      observer_ptr<Collider> collider = gameObject->findComponent<Collider>();
      if (collider != nullptr && collider->isActive() && collider->intersects(ray))
      {
        hitGameObjects.push_back(gameObject);
      }

      // Go through each child
      for (observer_ptr<GameObject> child : *gameObject)
      {
        if (child->isActive() && !child->hasComponent<Rendering::Canvas>())
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