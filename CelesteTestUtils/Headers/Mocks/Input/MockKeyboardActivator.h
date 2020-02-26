#pragma once

#include "CelesteTestUtilsDllExport.h"
#include "Input/KeyboardActivator.h"


namespace CelesteTestUtils
{
  class MockKeyboardActivator : public Celeste::Input::KeyboardActivator
  {
    DECLARE_SCRIPT(MockKeyboardActivator, CelesteTestUtilsDllExport)
  };
}
