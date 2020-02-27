#include "Input/KeyboardVisibility.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Input/InputManager.h"
#include "Rendering/Renderer.h"
#include "Screens/Screen.h"

using namespace Celeste::Rendering;


namespace Celeste::Input
{
  REGISTER_SCRIPT(KeyboardVisibility, 10)

    //------------------------------------------------------------------------------------------------
    KeyboardVisibility::KeyboardVisibility() :
    m_visibilityKey(GLFW_KEY_UNKNOWN),
    m_invisibilityKey(GLFW_KEY_UNKNOWN),
    m_inputMode(InputMode::kToggle),
    m_target()
  {
  }

  //------------------------------------------------------------------------------------------------
  void KeyboardVisibility::handleInput()
  {
    Inherited::handleInput();

    if (m_target == nullptr || (m_visibilityKey < 0 && m_invisibilityKey < 0))
    {
      ASSERT_FAIL();
      return;
    }

    if (observer_ptr<Renderer> renderer = m_target->findComponent<Renderer>(); renderer != nullptr)
    {
      bool currentState = renderer->isActive();

      if (m_inputMode == InputMode::kContinuous && m_visibilityKey > 0)
      {
        if (currentState != isKeyPressed(m_visibilityKey))
        {
          m_target->setActive(!currentState);
        }
      }
      else
      {
        if (currentState && m_invisibilityKey > 0 && isKeyTapped(m_invisibilityKey))
        {
          m_target->setActive(false);
        }
        else if (!currentState && m_visibilityKey > 0 && isKeyTapped(m_visibilityKey))
        {
          m_target->setActive(true);
        }
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void KeyboardVisibility::setTarget(StringId targetName)
  {
#if _DEBUG
    if (getGameObject() == nullptr || getGameObject()->getScreen() == nullptr)
    {
      ASSERT_FAIL();
      return;
    }
#endif

    if (targetName == static_cast<StringId>(0))
    {
      setTarget(nullptr);
    }
    else
    {
      observer_ptr<GameObject> target = getGameObject()->getScreen()->findGameObject(targetName);
      ASSERT_NOT_NULL(target);
      setTarget(target);
    }
  }
}