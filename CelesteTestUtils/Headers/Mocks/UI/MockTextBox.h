#pragma once

#include "CelesteTestUtilsDllExport.h"
#include "UI/TextBox.h"


namespace CelesteTestUtils
{
  class MockTextBox : public Celeste::UI::TextBox
  {
    DECLARE_UNMANAGED_COMPONENT(MockTextBox, CelesteTestUtilsDllExport)

    public:
      ~MockTextBox() override;

      Celeste::StringId getTextInputtedEventHandle_Public() const { return getTextInputtedEventHandle(); }
      Celeste::StringId getKeyPressedEventHandle_Public() const { return getKeyPressedEventHandle(); }
  };
}