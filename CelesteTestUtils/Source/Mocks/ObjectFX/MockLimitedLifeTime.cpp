#include "Mocks/ObjectFX/MockLimitedLifeTime.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteTestUtils
{
  REGISTER_UNMANAGED_COMPONENT(MockLimitedLifeTime, 10);

  MockLimitedLifeTime::MockLimitedLifeTime() = default;
}