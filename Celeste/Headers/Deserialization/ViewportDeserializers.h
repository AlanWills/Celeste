#pragma once

#include "Deserializers.h"
#include "Viewport/ViewportEnums.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport bool deserialize<ProjectionMode>(const std::string& text, ProjectionMode& output);
}