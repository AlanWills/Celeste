#pragma once

#include "CelesteDllExport.h"


namespace Celeste
{
  class CelesteDllExport OpenALState
  {
    public:
      static bool initialize();
      static bool terminate();

    private:
      OpenALState() = delete;
      ~OpenALState() = delete;
      OpenALState(const OpenALState&) = delete;
      OpenALState& operator=(const OpenALState&) = delete;

      static bool m_initialized;
  };
}