#pragma once

#include "DataConverters/ObjectFX/LimitedLifeTimeDataConverter.h"


namespace CelesteTestUtils
{
  class MockLimitedLifeTimeDataConverter : public Celeste::LimitedLifeTimeDataConverter
  {
    public:
      MockLimitedLifeTimeDataConverter() = default;
  };
}