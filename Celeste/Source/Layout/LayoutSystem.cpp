#include "Layout/LayoutSystem.h"
#include "Layout/ResolutionScaler.h"
#include "Viewport/OpenGLWindow.h"


namespace Celeste::Layout
{
  //------------------------------------------------------------------------------------------------
  LayoutSystem::LayoutSystem(const OpenGLWindow& glWindow) :
    m_glWindow(glWindow),
    m_viewportChangedHandle(glWindow.getViewportDimensionsChangedEvent().subscribe(
      [this](const glm::vec2& newResolution) 
      { 
        rescaleAll(newResolution); 
      }))
  {
  }

  //------------------------------------------------------------------------------------------------
  LayoutSystem::~LayoutSystem()
  {
    m_glWindow.getViewportDimensionsChangedEvent().unsubscribe(m_viewportChangedHandle);
  }

  //------------------------------------------------------------------------------------------------
  void LayoutSystem::update(float /*elapsedGameTime*/)
  {
    for (auto& resolutionScaler : ResolutionScaler::m_allocator)
    {
      if (resolutionScaler.needsRescale())
      {
        resolutionScaler.rescale(m_lastAppliedResolution, m_glWindow.getViewportDimensions());
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void LayoutSystem::rescaleAll(const glm::vec2& newResolution)
  {
    for (auto& resolutionScaler : ResolutionScaler::m_allocator)
    {
      resolutionScaler.rescale(m_lastAppliedResolution, newResolution);
    }

    m_lastAppliedResolution = newResolution;
  }
}