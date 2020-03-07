#pragma once

#include "CelesteDllExport.h"
#include "Memory/ObserverPtr.h"


namespace Celeste
{
  class Path;
}

namespace Celeste::SceneLoader
{
  CelesteDllExport void load(const Path& relativePathToLevelFile);
}