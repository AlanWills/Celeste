#include "Mocks/Physics/MockCollider.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteTestUtils
{
  REGISTER_SCRIPT(MockCollider, 10);

  //------------------------------------------------------------------------------------------------
  MockCollider::MockCollider() :
    m_onSetOffSetCalled(false)
  {
  }
}