#pragma once

#include "Objects/Script.h"
#include "Events/Event.h"

#include <thread>


namespace Celeste
{
  class LoadResourcesAsyncScript : public Script
  {
    DECLARE_SCRIPT(LoadResourcesAsyncScript, CelesteDllExport)

    public:
      const Event<>& getLoadCompleteEvent() const { return m_loadComplete; }

      CelesteDllExport void update(float secondsPerUpdate) override;

    private:
      using Inherited = Script;

      Event<> m_loadComplete;
  };
}