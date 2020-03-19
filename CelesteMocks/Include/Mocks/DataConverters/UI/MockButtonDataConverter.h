#pragma once

#include "DataConverters/UI/ButtonDataConverter.h"


namespace CelesteMocks
{
  class MockButtonDataConverter : public Celeste::ButtonDataConverter
  {
    public:
      MockButtonDataConverter() = default;
  };
}