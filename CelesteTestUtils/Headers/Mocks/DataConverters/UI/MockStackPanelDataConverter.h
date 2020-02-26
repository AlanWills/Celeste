#pragma once

#include "DataConverters/UI/StackPanelDataConverter.h"


namespace CelesteTestUtils
{
  class MockStackPanelDataConverter : public Celeste::StackPanelDataConverter
  {
    public:
      MockStackPanelDataConverter() = default;
  };
}