#include "Input/KeyboardActivator.h"
#include "Input/InputManager.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Screens/Screen.h"


namespace Celeste::Input
{
  REGISTER_COMPONENT(KeyboardActivator, 10)

    //------------------------------------------------------------------------------------------------
    KeyboardActivator::KeyboardActivator() :
    m_activationKey(GLFW_KEY_UNKNOWN),
    m_deactivationKey(GLFW_KEY_UNKNOWN),
    m_inputMode(InputMode::kToggle),
    m_target()
  {
  }

  //------------------------------------------------------------------------------------------------
  void KeyboardActivator::handleInput()
  {
    Inherited::handleInput();

    if ((m_activationKey < 0 && m_deactivationKey < 0) || m_target == nullptr)
    {
      ASSERT_FAIL();
      return;
    }

    if (m_inputMode == InputMode::kContinuous && m_activationKey > 0)
    {
      m_target->setActive(isKeyPressed(m_activationKey));
    }
    else if (m_inputMode == InputMode::kToggle)
    {
      if (m_target->isActive())
      {
        if (m_deactivationKey >= 0 && isKeyTapped(m_deactivationKey))
        {
          // Deactivate the gameobject and all other components/scripts but keep this one active
          m_target->setActive(false);
        }
      }
      else
      {
        if (m_activationKey >= 0 && isKeyTapped(m_activationKey))
        {
          // Activate the gameobject and all other components/scripts
          m_target->setActive(true);
        }
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void KeyboardActivator::setTarget(StringId targetName)
  {
//#if _DEBUG
//    if (getGameObject() == nullptr || getGameObject()->getScreen() == nullptr)
//    {
//      ASSERT_FAIL();
//      return;
//    }
//#endif
//
//    if (targetName == static_cast<StringId>(0))
//    {
//      // If we have set the name to the empty string/name we clear the target
//      setTarget(nullptr);
//    }
//    else
//    {
//      observer_ptr<GameObject> target = getGameObject()->getScreen()->findGameObject(targetName);
//      ASSERT_NOT_NULL(target);
//      setTarget(target);
//    }
  }
}