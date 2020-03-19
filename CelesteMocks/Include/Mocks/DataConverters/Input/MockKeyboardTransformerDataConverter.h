#pragma once

#include "DataConverters/Input/KeyboardTransformerDataConverter.h"


namespace CelesteMocks
{
  class MockKeyboardTransformerDataConverter : public Celeste::KeyboardTransformerDataConverter
  {
    public:
      MockKeyboardTransformerDataConverter() = default;
  };
}