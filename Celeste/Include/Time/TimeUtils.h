#pragma once

#include "Clock.h"


namespace Celeste::Time
{
  CelesteDllExport Clock& getClock();
  CelesteDllExport float getElapsedDeltaTime();
}