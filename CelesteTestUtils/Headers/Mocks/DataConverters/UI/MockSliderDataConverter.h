#pragma once

#include "DataConverters/UI/SliderDataConverter.h"


namespace CelesteTestUtils
{
  class MockSliderDataConverter : public Celeste::SliderDataConverter
  {
    public:
      MockSliderDataConverter() = default;
  };
}