#include "Maths/RandomGenerator.h"


namespace Celeste
{
  namespace Random
  {
    //------------------------------------------------------------------------------------------------
    size_t generate(size_t min, size_t max)
    {
      return (size_t)generate((float)min, (float)(max + 1));
    }

    //------------------------------------------------------------------------------------------------
    float generate(float min, float max)
    {
      return min + (max - min) * ((float)rand() / RAND_MAX);
    }
  }
}