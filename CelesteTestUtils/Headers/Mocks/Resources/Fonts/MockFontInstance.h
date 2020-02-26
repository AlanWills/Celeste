#pragma once

#include "Resources/Fonts/FontInstance.h"


namespace CelesteTestUtils
{

class MockFontInstance : public Celeste::Resources::FontInstance
{
  public:
    size_t getNumberOfCharacters_Public() const { return getNumberOfCharacters(); }
};

}