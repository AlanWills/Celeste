#pragma once

#include "CelesteDllExport.h"

#include <random>


namespace Celeste
{
  namespace Random
  {
    inline void seed(unsigned int seed) { srand(seed); }

    CelesteDllExport size_t generate(size_t min, size_t max);
    CelesteDllExport float generate(float min = 0, float max = 1);
  };
}