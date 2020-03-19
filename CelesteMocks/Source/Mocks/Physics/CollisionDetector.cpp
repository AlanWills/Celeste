#include "Mocks/Physics/CollisionDetector.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteMocks
{
  REGISTER_UNMANAGED_COMPONENT(CollisionDetector, 4)

  //------------------------------------------------------------------------------------------------
  CollisionDetector::CollisionDetector(GameObject& gameObject) :
    Inherited(gameObject),
    m_triggerEnterCount(0),
    m_triggerCount(0),
    m_triggerExitCount(0),
    m_collisionEnterCount(0),
    m_collisionCount(0),
    m_collisionExitCount(0)
  {
  }
}