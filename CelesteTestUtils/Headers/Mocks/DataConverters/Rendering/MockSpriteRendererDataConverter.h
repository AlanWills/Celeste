#pragma once

#include "DataConverters/Rendering/SpriteRendererDataConverter.h"


namespace CelesteTestUtils
{
  class MockSpriteRendererDataConverter : public Celeste::SpriteRendererDataConverter
  {
    public:
      MockSpriteRendererDataConverter() = default;
  };
}