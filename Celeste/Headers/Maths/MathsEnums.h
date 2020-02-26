#pragma once

#include "CelesteDllExport.h"
#include "glm/glm.hpp"
#include "Utils/ToString.h"

#include <string>


namespace Celeste
{
  namespace Maths
  {
    enum class Space
    {
      kWorld,
      kLocal
    };
  }

  //------------------------------------------------------------------------------------------------
  template <>
  CelesteDllExport std::string to_string(Maths::Space space);
}