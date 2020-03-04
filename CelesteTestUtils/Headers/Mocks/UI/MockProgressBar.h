#pragma once

#include "CelesteTestUtilsDllExport.h"
#include "UI/ProgressBar.h"


namespace CelesteTestUtils
{
  class MockProgressBar : public Celeste::UI::ProgressBar
  {
    DECLARE_UNMANAGED_COMPONENT(MockProgressBar, CelesteTestUtilsDllExport)
  };
}