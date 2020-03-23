#include "Mocks/Input/MockKeyboardTransformer.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteMocks
{
  REGISTER_COMPONENT(MockKeyboardTransformer, 10)

  MockKeyboardTransformer::MockKeyboardTransformer(GameObject& gameObject) :
    Inherited(gameObject)
  {
  }
}