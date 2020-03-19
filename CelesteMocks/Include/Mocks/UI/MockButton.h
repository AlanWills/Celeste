#pragma once

#include "StaticLibExport.h"
#include "UI/Button.h"


namespace CelesteMocks
{
  class MockButton : public Celeste::UI::Button
  {
    DECLARE_UNMANAGED_COMPONENT(MockButton, StaticLibExport)

    public:
      Celeste::UI::Button::ButtonState getButtonState_Public() const { return getButtonState(); }
      void setButtonState_Public(Celeste::UI::Button::ButtonState state) { setButtonState(state); }

    private:
      using Inherited = Celeste::UI::Button;
  };
}