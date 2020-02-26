#pragma once

#include "CelesteDllExport.h"
#include "Callback.h"


namespace Celeste
{
  class GameObject;

  class ExitGame
  {
    DECLARE_CALLBACK(ExitGame)

    public:
      CelesteDllExport void operator()(GameObject& gameObject, const std::string& args);
  };
}