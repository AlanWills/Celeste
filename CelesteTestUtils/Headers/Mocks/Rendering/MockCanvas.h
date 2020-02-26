#pragma once

#include "CelesteTestUtilsDllExport.h"
#include "Rendering/Canvas.h"


namespace CelesteTestUtils
{
  class MockCanvas : public Celeste::Rendering::Canvas
  {
    DECLARE_SCRIPT(MockCanvas, CelesteTestUtilsDllExport)
  };
}