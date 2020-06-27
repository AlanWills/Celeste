#include "Layout/LayoutSystem.h"
#include "Layout/ResolutionScaler.h"
#include "Viewport/OpenGLWindow.h"


namespace Celeste::Layout
{
  //------------------------------------------------------------------------------------------------
  LayoutSystem::LayoutSystem(const OpenGLWindow& glWindow) :
    m_glWindow(glWindow),
    m_resolutionChangedHandle(glWindow.getResolutionChangedEvent().subscribe(
      [this](const glm::vec2& clientSafeArea)
      { 
        rescaleAll(clientSafeArea);
      }))
    , m_lastAppliedContentArea(glWindow.getContentArea())
  {
  }

  //------------------------------------------------------------------------------------------------
  LayoutSystem::~LayoutSystem()
  {
    m_glWindow.getResolutionChangedEvent().unsubscribe(m_resolutionChangedHandle);
  }

  //------------------------------------------------------------------------------------------------
  void LayoutSystem::update(float /*elapsedGameTime*/)
  {
    for (auto& resolutionScaler : ResolutionScaler::m_allocator)
    {
      if (resolutionScaler.needsRescale())
      {
        resolutionScaler.rescale(m_lastAppliedContentArea, m_glWindow.getContentArea());
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void LayoutSystem::rescaleAll(const glm::vec2& newContentArea)
  {
    for (auto& resolutionScaler : ResolutionScaler::m_allocator)
    {
      resolutionScaler.rescale(m_lastAppliedContentArea, newContentArea);
    }

    m_lastAppliedContentArea = newContentArea;
  }
}