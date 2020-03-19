#include "Mocks/Physics/MockCollider.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteMocks
{
  REGISTER_UNMANAGED_COMPONENT(MockCollider, 10);

  //------------------------------------------------------------------------------------------------
  MockCollider::MockCollider(GameObject& gameObject) :
    Inherited(gameObject),
    m_onSetOffSetCalled(false)
  {
  }
}