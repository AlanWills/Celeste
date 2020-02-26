#include "Mocks/Objects/MockScript.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteTestUtils
{
  REGISTER_SCRIPT(MockScript, 10)

  //------------------------------------------------------------------------------------------------
  MockScript::MockScript() :
    m_handleInputCalled(false),
    m_updateCalled(false),
    m_onDeathCalled(false)
  { 
  }

  //------------------------------------------------------------------------------------------------
  void MockScript::onHandleInput()
  {
    Inherited::onHandleInput();

    m_handleInputCalled = true;
  }

  //------------------------------------------------------------------------------------------------
  void MockScript::onUpdate(float secondsPerUpdate)
  {
    Inherited::onUpdate(secondsPerUpdate);

    m_updateCalled = true;
  }

  //------------------------------------------------------------------------------------------------
  void MockScript::onDeath()
  {
    Inherited::onDeath();

    m_onDeathCalled = true;
    m_handleInputCalled = false;
    m_updateCalled = false;
  }
}