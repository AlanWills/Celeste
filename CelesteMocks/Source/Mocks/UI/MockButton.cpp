#include "Mocks/UI/MockButton.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteMocks
{
  REGISTER_COMPONENT(MockButton, 10);

  MockButton::MockButton(GameObject& gameObject) :
    Inherited(gameObject)
  {
  }
}