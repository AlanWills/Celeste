#pragma once

#include "DataConverters/UI/ButtonDataConverter.h"


namespace CelesteTestUtils
{
  class MockButtonDataConverter : public Celeste::ButtonDataConverter
  {
    public:
      MockButtonDataConverter() = default;
  };
}