#pragma once

#include "CelesteTestUtilsDllExport.h"
#include "Rendering/Canvas.h"


namespace CelesteTestUtils
{
  class MockCanvas : public Celeste::Rendering::Canvas
  {
    DECLARE_UNMANAGED_COMPONENT(MockCanvas, CelesteTestUtilsDllExport)
  };
}