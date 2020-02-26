#pragma once

#include "CelesteDllExport.h"
#include "Callback.h"


namespace Celeste
{
  class GameObject;

  class KillGameObject
  {
    DECLARE_CALLBACK(KillGameObject)

    public:
      CelesteDllExport void operator()(GameObject& gameObject, const std::string& args);
  };
}