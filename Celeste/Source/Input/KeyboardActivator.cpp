#include "Input/KeyboardActivator.h"
#include "Input/InputManager.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Screens/Screen.h"


namespace Celeste::Input
{
  REGISTER_MANAGED_COMPONENT(KeyboardActivator, 10)

  //------------------------------------------------------------------------------------------------
  KeyboardActivator::KeyboardActivator(GameObject& gameObject) :
    Inherited(gameObject),
    m_activationKey(GLFW_KEY_UNKNOWN),
    m_deactivationKey(GLFW_KEY_UNKNOWN),
    m_inputMode(InputMode::kToggle)
  {
  }

  //------------------------------------------------------------------------------------------------
  void KeyboardActivator::handleInput()
  {
    Inherited::handleInput();

    //ASSERT_FAIL_MSG("TODO - this won't work cos the script will be disabled when we disable it.");

#if _DEBUG
    if (m_activationKey < 0 && m_deactivationKey < 0)
    {
      ASSERT_FAIL();
      return;
    }
#endif

    if (m_inputMode == InputMode::kContinuous && m_activationKey > 0)
    {
      getGameObject()->setActive(isKeyPressed(m_activationKey));
    }
    else if (m_inputMode == InputMode::kToggle)
    {
      if (getGameObject()->isActive())
      {
        if (m_deactivationKey >= 0 && isKeyTapped(m_deactivationKey))
        {
          // Deactivate the gameobject and all other components/scripts but keep this one active
          getGameObject()->setActive(false);
        }
      }
      else
      {
        if (m_activationKey >= 0 && isKeyTapped(m_activationKey))
        {
          // Activate the gameobject and all other components/scripts
          getGameObject()->setActive(true);
        }
      }
    }
  }
}