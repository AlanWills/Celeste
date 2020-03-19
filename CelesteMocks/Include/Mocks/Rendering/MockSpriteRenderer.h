#pragma once

#include "StaticLibExport.h"
#include "Rendering/SpriteRenderer.h"


namespace CelesteMocks
{
  class MockSpriteRenderer : public Celeste::Rendering::SpriteRenderer
  {
    DECLARE_UNMANAGED_COMPONENT(MockSpriteRenderer, StaticLibExport)

    public:
      void render(const Celeste::Resources::Program& program, const glm::mat4& viewModelMatrix) const override
      {
        Celeste::Rendering::SpriteRenderer::render(program, viewModelMatrix);
        m_renderCalled = true; 
      }

      bool isRenderCalled() const { return m_renderCalled; }

    private:
      using Inherited = Celeste::Rendering::SpriteRenderer;

      mutable bool m_renderCalled;
  };
}