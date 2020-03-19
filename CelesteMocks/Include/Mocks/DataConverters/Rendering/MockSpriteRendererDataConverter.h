#pragma once

#include "DataConverters/Rendering/SpriteRendererDataConverter.h"


namespace CelesteMocks
{
  class MockSpriteRendererDataConverter : public Celeste::SpriteRendererDataConverter
  {
    public:
      MockSpriteRendererDataConverter() = default;
  };
}