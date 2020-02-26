#pragma once

#include "CelesteTestUtilsDllExport.h"
#include "UI/Button.h"


namespace CelesteTestUtils
{
  class MockButton : public Celeste::UI::Button
  {
    DECLARE_SCRIPT(MockButton, CelesteTestUtilsDllExport)

    public:
      Celeste::UI::Button::ButtonState getButtonState_Public() const { return getButtonState(); }
      void setButtonState_Public(Celeste::UI::Button::ButtonState state) { setButtonState(state); }
  };
}