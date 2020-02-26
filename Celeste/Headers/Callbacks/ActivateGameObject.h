#pragma once

#include "CelesteDllExport.h"
#include "Callback.h"


namespace Celeste
{
  class GameObject;

  struct ActivateGameObject
  {
    DECLARE_CALLBACK(ActivateGameObject)

    public:
      CelesteDllExport void operator()(GameObject& gameObject, const std::string& arg);
  };
}