#pragma once

#include "CelesteDllExport.h"
#include "Callback.h"


namespace Celeste
{
  class GameObject;

  struct CelesteDllExport RenderGameObject
  {
    DECLARE_CALLBACK(RenderGameObject)

    public:
      void operator()(GameObject& gameObject, const std::string& arg);
  };
}