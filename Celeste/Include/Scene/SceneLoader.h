#pragma once

#include "CelesteDllExport.h"
#include "Memory/ObserverPtr.h"

#include <vector>
#include <tuple>


namespace Celeste
{
  class Path;
  class GameObject;
}

namespace Celeste::SceneLoader
{
  CelesteDllExport std::tuple<bool, std::vector<GameObject*>> load(const Path& relativePathToLevelFile);
}