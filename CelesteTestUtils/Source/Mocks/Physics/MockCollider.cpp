#include "Mocks/Physics/MockCollider.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteTestUtils
{
  REGISTER_UNMANAGED_COMPONENT(MockCollider, 10);

  //------------------------------------------------------------------------------------------------
  MockCollider::MockCollider() :
    m_onSetOffSetCalled(false)
  {
  }
}