#pragma once

#include "Objects/Entity.h"
#include "Rendering/RenderUtils.h"


namespace Celeste::Rendering
{
  class RenderManager : public Entity
  {
    public:
      CelesteDllExport RenderManager();
      CelesteDllExport ~RenderManager() override;

      RenderManager(const RenderManager&) = delete;
      RenderManager& operator=(const RenderManager&) = delete;

      CelesteDllExport void render(float lag);

      void handleInput() override;
      void update(float elapsedGameTime) override;

    private:
      using Inherited = Entity;
  };
}