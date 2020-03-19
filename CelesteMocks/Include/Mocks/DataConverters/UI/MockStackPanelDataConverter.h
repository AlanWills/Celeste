#pragma once

#include "DataConverters/UI/StackPanelDataConverter.h"


namespace CelesteMocks
{
  class MockStackPanelDataConverter : public Celeste::StackPanelDataConverter
  {
    public:
      MockStackPanelDataConverter() = default;
  };
}