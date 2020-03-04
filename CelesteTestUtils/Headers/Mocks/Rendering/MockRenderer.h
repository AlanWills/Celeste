#pragma once

#include "CelesteTestUtilsDllExport.h"
#include "Rendering/Renderer.h"


namespace CelesteTestUtils
{
  class MockRenderer : public Celeste::Rendering::Renderer
  {
    DECLARE_UNMANAGED_COMPONENT(MockRenderer, CelesteTestUtilsDllExport)

    public:
      void render(const Celeste::Resources::Program& program, const glm::mat4& viewModelMatrix) const override { m_renderCalled = true; }

      glm::vec2 getDimensions() const override { return m_dimensions; }
      void setDimensions(const glm::vec2& dimensions) { m_dimensions = dimensions; }

      bool isRenderCalled() const { return m_renderCalled; }

    private:
      mutable bool m_renderCalled;
      glm::vec2 m_dimensions;
  };
}