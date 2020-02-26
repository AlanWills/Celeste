#pragma once

#include "CelesteDllExport.h"
#include "Callback.h"


namespace Celeste
{
  class GameObject;

  struct KillScreen
  {
    DECLARE_CALLBACK(KillScreen)

    public:
      CelesteDllExport void operator()(GameObject& gameObject, const std::string& arg);
  };
}