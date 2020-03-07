#include "Mocks/UI/MockTextBox.h"
#include "Input/InputManager.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteTestUtils
{
  REGISTER_UNMANAGED_COMPONENT(MockTextBox, 10);

  //------------------------------------------------------------------------------------------------
  MockTextBox::MockTextBox(GameObject& gameObject) :
    Inherited(gameObject)
  {
  }
}