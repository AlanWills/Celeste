#pragma once

#include "CelesteDllExport.h"


namespace Celeste
{
  class Path;

  namespace Resources
  {
    class ResourceManager;

    CelesteDllExport ResourceManager& getResourceManager();
    CelesteDllExport const Path& getResourcesDirectory();
  }
}