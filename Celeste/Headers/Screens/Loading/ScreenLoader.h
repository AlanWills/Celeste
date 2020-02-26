#pragma once

#include "CelesteDllExport.h"
#include "Memory/ObserverPtr.h"


namespace Celeste
{
  class Screen;
  class Path;
}

namespace Celeste::ScreenLoader
{
  CelesteDllExport observer_ptr<Screen> load(const Path& relativePathToLevelFile);
}