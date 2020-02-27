#include "Rendering/RenderManager.h"
#include "Rendering/Canvas.h"


namespace Celeste::Rendering
{
  //------------------------------------------------------------------------------------------------
  RenderManager::RenderManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  RenderManager::~RenderManager()
  {
    Canvas::m_componentAllocator.deallocateAll();
  }

  //------------------------------------------------------------------------------------------------
  void RenderManager::handleInput()
  {
    Inherited::handleInput();

    Canvas::m_componentAllocator.handleInput();
  }

  //------------------------------------------------------------------------------------------------
  void RenderManager::update(float elapsedGameTime)
  {
    Inherited::update(elapsedGameTime);

    Canvas::m_componentAllocator.update(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void RenderManager::render(float lag)
  {
    std::vector<std::reference_wrapper<Canvas>> canvasses;
    for (Canvas& renderer : Canvas::m_componentAllocator)
    {
      if (renderer.isActive())
      {
        canvasses.push_back(renderer);
      }
    }

    // Sort the active canvas renderers in z depth order to get correct render order
    std::sort(canvasses.begin(), canvasses.end(), [](Canvas& lhs, Canvas& rhs) -> bool
      {
        return lhs.getTransform()->getWorldTranslation().z < rhs.getTransform()->getWorldTranslation().z;
      });

    // Now render the canvasses in correct order
    for (Canvas& renderer : canvasses)
    {
      renderer.render(lag);
    }
  }
}