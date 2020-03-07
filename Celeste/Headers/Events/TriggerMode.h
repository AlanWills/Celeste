#pragma once

#include "CelesteDllExport.h"
#include "Utils/ToString.h"

#include <string>


namespace Celeste::Events
{
  enum class TriggerMode
  {
    kOnce,
    kUnlimited
  };
}

namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport std::string to_string(Events::TriggerMode triggerMode);

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport bool from_string(const std::string& text, Events::TriggerMode& triggerMode);
}