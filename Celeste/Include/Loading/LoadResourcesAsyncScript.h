#pragma once

#include "Objects/Component.h"
#include "Events/Event.h"

#include <thread>


namespace Celeste
{
  class LoadResourcesAsyncScript : public Component
  {
    DECLARE_UNMANAGED_COMPONENT(LoadResourcesAsyncScript, CelesteDllExport)

    public:
      const Event<>& getLoadCompleteEvent() const { return m_loadComplete; }

      CelesteDllExport void update() override;

    private:
      using Inherited = Component;

      Event<> m_loadComplete;
  };
}