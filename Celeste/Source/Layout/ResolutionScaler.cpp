#include "Layout/ResolutionScaler.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Scene/SceneUtils.h"


namespace Celeste::Layout
{
  REGISTER_COMPONENT(ResolutionScaler, 10);

  //------------------------------------------------------------------------------------------------
  ResolutionScaler::ResolutionScaler(GameObject& gameObject) :
    Inherited(gameObject),
    m_targetResolution(1920, 1080)
  {
  }

  //------------------------------------------------------------------------------------------------
  void ResolutionScaler::setTargetResolution(const glm::vec2& targetResolution)
  {
    ASSERT(targetResolution.x != 0);
    ASSERT(targetResolution.y != 0);
    m_targetResolution = targetResolution;
    m_needsRescale = true;
  }

  //------------------------------------------------------------------------------------------------
  void ResolutionScaler::rescale(const glm::vec2& oldResolution, const glm::vec2& newResolution)
  {
    ASSERT(m_targetResolution.x != 0);
    ASSERT(m_targetResolution.y != 0);

    Transform* transform = getGameObject().getTransform();

    if (oldResolution != newResolution)
    {
      ASSERT(oldResolution.x != 0);
      ASSERT(oldResolution.y != 0);

      // Undo old resolution scaling effects
      transform->scale(m_targetResolution / oldResolution);

      // Set translation back to original position
      transform->setTranslation(glm::vec2(transform->getTranslation()) * m_targetResolution / oldResolution);
    }

    ASSERT(newResolution.x != 0);
    ASSERT(newResolution.y != 0);

    // Apply new resolution scaling effects
    transform->scale(newResolution / m_targetResolution);

    // Shift position to account for scaling + current translation
    transform->setTranslation(glm::vec2(transform->getTranslation()) * newResolution / m_targetResolution);

    m_needsRescale = false;
  }
}