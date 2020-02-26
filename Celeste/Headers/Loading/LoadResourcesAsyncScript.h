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

    protected:
      CelesteDllExport void onUpdate(float secondsPerUpdate) override;
      CelesteDllExport void onDeath() override;

    private:
      typedef Script Inherited;

      Event<> m_loadComplete;

      // Don't like this, but running into copy constructor deletion issues
      // If there is a way around this, I'm all ears
      //std::thread* m_loadingThread;
  };
}