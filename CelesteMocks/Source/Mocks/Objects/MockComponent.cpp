#include "Mocks/Objects/MockComponent.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteMocks
{
  REGISTER_COMPONENT(MockComponent, 10)

  //------------------------------------------------------------------------------------------------
  MockComponent::MockComponent(GameObject& gameObject) :
    Inherited(gameObject),
    m_updateCalled(false)
  {
  }
}