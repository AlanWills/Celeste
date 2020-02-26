#pragma once

#include "Objects/Entity.h"
#include "Rendering/RenderUtils.h"


namespace Celeste::Rendering
{
  class RenderManager : public Entity
  {
    public:
      CelesteDllExport RenderManager();
      RenderManager(const RenderManager&) = delete;
      RenderManager& operator=(const RenderManager&) = delete;

      CelesteDllExport void render(float lag);

    protected:
      void onHandleInput() override;
      void onUpdate(float elapsedGameTime) override;
      void onDeath() override;

    private:
      using Inherited = Entity;
  };
}