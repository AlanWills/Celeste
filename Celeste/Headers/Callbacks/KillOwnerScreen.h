#pragma once

#include "CelesteDllExport.h"
#include "Callback.h"


namespace Celeste
{
  class GameObject;

  struct KillOwnerScreen
  {
    DECLARE_CALLBACK(KillOwnerScreen)

    public:
      CelesteDllExport void operator()(GameObject& gameObject, const std::string& arg = "");
  };
}