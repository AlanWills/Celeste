#include "Mocks/Objects/MockComponent.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteTestUtils
{
  REGISTER_SCRIPT(MockComponent, 10)

  //------------------------------------------------------------------------------------------------
  MockComponent::MockComponent() :
    m_onSetGameObjectCalled(false),
    m_handleInputCalled(false),
    m_updateCalled(false),
    m_onDeathCalled(false)
  {
  }
}