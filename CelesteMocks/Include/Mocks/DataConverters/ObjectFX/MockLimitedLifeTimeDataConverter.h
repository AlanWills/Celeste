#pragma once

#include "DataConverters/ObjectFX/LimitedLifeTimeDataConverter.h"


namespace CelesteMocks
{
  class MockLimitedLifeTimeDataConverter : public Celeste::LimitedLifeTimeDataConverter
  {
    public:
      MockLimitedLifeTimeDataConverter() = default;
  };
}