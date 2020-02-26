#pragma once

#include "CelesteTestUtilsDllExport.h"
#include "Rendering/SpriteRenderer.h"


namespace CelesteTestUtils
{
  class MockSpriteRenderer : public Celeste::Rendering::SpriteRenderer
  {
    DECLARE_SCRIPT(MockSpriteRenderer, CelesteTestUtilsDllExport)

    public:
      void render(const Celeste::Resources::Program& program, const glm::mat4& viewModelMatrix) const override
      {
        Celeste::Rendering::SpriteRenderer::render(program, viewModelMatrix);
        m_renderCalled = true; 
      }

      bool isRenderCalled() const { return m_renderCalled; }

    protected:
      void onDeath() override
      {
        Celeste::Rendering::SpriteRenderer::onDeath();
        m_renderCalled = false;
      }

    private:
      mutable bool m_renderCalled;
  };
}