#pragma once

#include "Resources/Fonts/Font.h"


namespace CelesteTestUtils
{

class MockFont : public Celeste::Resources::Font
{
  public:
    size_t getNumberOfHeightsLoaded_Public() const { return getNumberOfHeightsLoaded(); }
};

}