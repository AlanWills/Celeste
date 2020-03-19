#include "Mocks/Objects/MockUnmanagedComponent.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteTestUtils
{
  REGISTER_UNMANAGED_COMPONENT(MockUnmanagedComponent, 10);

  MockUnmanagedComponent::MockUnmanagedComponent(Celeste::GameObject& gameObject) :
    Celeste::Component(gameObject)
  {
  }
}