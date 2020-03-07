#pragma once

#include "CelesteTestUtilsDllExport.h"
#include "Rendering/TextRenderer.h"


namespace CelesteTestUtils
{
  class MockTextRenderer : public Celeste::Rendering::TextRenderer
  {
    DECLARE_UNMANAGED_COMPONENT(MockTextRenderer, CelesteTestUtilsDllExport)

    public:
      float getXPosition_Public(float halfLineWidth) const
      {
        return getXPosition(halfLineWidth);
      }

      float getYPosition_Public(float halfMaxWidth) const
      {
        return getYPosition(halfMaxWidth);
      }

    private:
      using Inherited = Celeste::Rendering::TextRenderer;
  };
}