#pragma once

#include "CelesteTestUtilsDllExport.h"
#include "Input/KeyboardVisibility.h"


namespace CelesteTestUtils
{
  class MockKeyboardVisibility : public Celeste::Input::KeyboardVisibility
  {
    DECLARE_SCRIPT(MockKeyboardVisibility, CelesteTestUtilsDllExport)
  };
}
