#pragma once

#include "CelesteDllExport.h"
#include "Callback.h"


namespace Celeste
{
  class GameObject;

  struct ExecuteLuaScript
  {
    DECLARE_CALLBACK(ExecuteLuaScript)

    public:
      CelesteDllExport void operator()(GameObject& gameObject, const std::string& arg);
  };
}