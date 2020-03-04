#pragma once

#include "CelesteTestUtilsDllExport.h"
#include "Rendering/SpriteRenderer.h"


namespace CelesteTestUtils
{
  class MockSpriteRenderer : public Celeste::Rendering::SpriteRenderer
  {
    DECLARE_UNMANAGED_COMPONENT(MockSpriteRenderer, CelesteTestUtilsDllExport)

    public:
      void render(const Celeste::Resources::Program& program, const glm::mat4& viewModelMatrix) const override
      {
        Celeste::Rendering::SpriteRenderer::render(program, viewModelMatrix);
        m_renderCalled = true; 
      }

      bool isRenderCalled() const { return m_renderCalled; }

    private:
      mutable bool m_renderCalled;
  };
}