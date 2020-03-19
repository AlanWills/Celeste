#pragma once

#include "DataConverters/GraphicalFX/OpacityLerperDataConverter.h"


namespace CelesteTestUtils
{
  class MockOpacityLerperDataConverter : public Celeste::OpacityLerperDataConverter
  {
    public:
      MockOpacityLerperDataConverter() = default;
  };
}