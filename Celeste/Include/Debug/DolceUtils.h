#pragma once

#if _DEBUG

#include "CelesteDllExport.h"


namespace Dolce
{
  class Dolce;
}

namespace Celeste::Debug
{
  CelesteDllExport Dolce::Dolce& getDolce();
}

#endif