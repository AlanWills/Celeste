#include "Mocks/Objects/MockComponent.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteTestUtils
{
  REGISTER_UNMANAGED_COMPONENT(MockComponent, 10)

  //------------------------------------------------------------------------------------------------
  MockComponent::MockComponent(GameObject& gameObject) :
    Inherited(gameObject),
    m_handleInputCalled(false),
    m_updateCalled(false)
  {
  }
}