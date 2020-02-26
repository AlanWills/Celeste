#pragma once

#include "CelesteDllExport.h"
#include "Callback.h"


namespace Celeste
{
  class GameObject;

  struct TransitionToScreen
  {
    DECLARE_CALLBACK(TransitionToScreen)

    public:
      CelesteDllExport void operator()(GameObject& gameObject, const std::string& arg);
  };
}