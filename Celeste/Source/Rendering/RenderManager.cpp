#include "Rendering/RenderManager.h"
#include "Rendering/Canvas.h"
#include "Algorithms/EntityAlgorithms.h"
#include "Maths/Transform.h"


namespace Celeste::Rendering
{
  //------------------------------------------------------------------------------------------------
  RenderManager::RenderManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  RenderManager::~RenderManager()
  {
    Canvas::m_allocator.deallocateAll();
  }

  //------------------------------------------------------------------------------------------------
  void RenderManager::handleInput()
  {
    Inherited::handleInput();

    Algorithms::handleInput(Canvas::m_allocator);
  }

  //------------------------------------------------------------------------------------------------
  void RenderManager::update(float elapsedGameTime)
  {
    Inherited::update(elapsedGameTime);

    Algorithms::update(elapsedGameTime, Canvas::m_allocator);
  }

  //------------------------------------------------------------------------------------------------
  void RenderManager::render(float lag)
  {
    std::vector<std::reference_wrapper<Canvas>> canvasses;
    for (Canvas& renderer : Canvas::m_allocator)
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