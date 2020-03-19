#pragma once

#include "DataConverters/GraphicalFX/OpacityLerperDataConverter.h"


namespace CelesteMocks
{
  class MockOpacityLerperDataConverter : public Celeste::OpacityLerperDataConverter
  {
    public:
      MockOpacityLerperDataConverter() = default;
  };
}