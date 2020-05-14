#pragma once

#include "CelesteDllExport.h"


namespace Dolce
{
  class IDolce;
}

namespace Celeste::Debug
{
  CelesteDllExport Dolce::IDolce& getDolce();
}