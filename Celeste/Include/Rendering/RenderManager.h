#pragma once

#include "System/ISystem.h"
#include "Rendering/RenderUtils.h"


namespace Celeste::Rendering
{
  class RenderManager : public System::ISystem
  {
    public:
      CelesteDllExport RenderManager();
      CelesteDllExport ~RenderManager() override;

      RenderManager(const RenderManager&) = delete;
      RenderManager& operator=(const RenderManager&) = delete;

      CelesteDllExport void render(float lag);

      void update(float elapsedGameTime) override;

    private:
      using Inherited = System::ISystem;
  };
}