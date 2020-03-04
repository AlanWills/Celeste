#include "Mocks/Objects/MockScript.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteTestUtils
{
  REGISTER_UNMANAGED_COMPONENT(MockScript, 10)

  //------------------------------------------------------------------------------------------------
  MockScript::MockScript() :
    m_handleInputCalled(false),
    m_updateCalled(false)
  { 
  }

  //------------------------------------------------------------------------------------------------
  void MockScript::handleInput()
  {
    Inherited::handleInput();

    m_handleInputCalled = true;
  }

  //------------------------------------------------------------------------------------------------
  void MockScript::update(float secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    m_updateCalled = true;
  }
}