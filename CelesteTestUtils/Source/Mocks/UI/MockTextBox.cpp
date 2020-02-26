#include "Mocks/UI/MockTextBox.h"
#include "Input/InputManager.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteTestUtils
{
  REGISTER_SCRIPT(MockTextBox, 10);

  //------------------------------------------------------------------------------------------------
  MockTextBox::MockTextBox() = default;

  //------------------------------------------------------------------------------------------------
  MockTextBox::~MockTextBox()
  {
    Input::getKeyboard().getTextInputtedEvent().unsubscribe(getTextInputtedEventHandle());
    Input::getKeyboard().getKeyPressedEvent().unsubscribe(getKeyPressedEventHandle());
  }
}