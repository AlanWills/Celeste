#pragma once

#include "CelesteTestUtilsDllExport.h"
#include "ObjectFX/LimitedLifeTime.h"


namespace CelesteTestUtils
{
  class MockLimitedLifeTime : public Celeste::LimitedLifeTime
  {
    DECLARE_UNMANAGED_COMPONENT(MockLimitedLifeTime, CelesteTestUtilsDllExport)
  };
}
