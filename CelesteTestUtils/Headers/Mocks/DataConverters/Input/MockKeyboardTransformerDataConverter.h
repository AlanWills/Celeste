#pragma once

#include "DataConverters/Input/KeyboardTransformerDataConverter.h"


namespace CelesteTestUtils
{
  class MockKeyboardTransformerDataConverter : public Celeste::KeyboardTransformerDataConverter
  {
    public:
      MockKeyboardTransformerDataConverter() = default;
  };
}