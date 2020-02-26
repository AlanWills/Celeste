#pragma once

#include "CelesteDllExport.h"

#include <string>


namespace Celeste
{
  enum class ProjectionMode
  {
    kOrthographic,
    kPerspective
  };

  //------------------------------------------------------------------------------------------------
  CelesteDllExport std::string to_string(ProjectionMode projectionMode);
}