#include "Mocks/Animation/MockAnimator.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteMocks
{
  REGISTER_UNMANAGED_COMPONENT(MockAnimator, 10);

  MockAnimator::MockAnimator(GameObject& gameObject) :
    Inherited(gameObject)
  {
  }
}