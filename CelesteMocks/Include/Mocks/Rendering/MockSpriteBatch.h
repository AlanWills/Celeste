#pragma once

#include "Rendering/SpriteBatch.h"


namespace CelesteMocks
{

class MockSpriteBatch : public Celeste::Rendering::SpriteBatch
{
  public:
    size_t renderers_size_Public() const { return renderers_size(); }
};

}