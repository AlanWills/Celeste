#include "Mocks/Animation/MockAnimator.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteTestUtils
{
  REGISTER_UNMANAGED_COMPONENT(MockAnimator, 10);

  MockAnimator::MockAnimator(GameObject& gameObject) :
    Inherited(gameObject)
  {
  }
}