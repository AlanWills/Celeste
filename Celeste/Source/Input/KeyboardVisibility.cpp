#include "Input/KeyboardVisibility.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Input/InputManager.h"
#include "Rendering/Renderer.h"

using namespace Celeste::Rendering;


namespace Celeste::Input
{
  REGISTER_COMPONENT(KeyboardVisibility, 10)

  //------------------------------------------------------------------------------------------------
  KeyboardVisibility::KeyboardVisibility(GameObject& gameObject) :
    Inherited(gameObject),
    m_visibilityKey(GLFW_KEY_UNKNOWN),
    m_invisibilityKey(GLFW_KEY_UNKNOWN),
    m_inputMode(InputMode::kToggle)
  {
  }

  //------------------------------------------------------------------------------------------------
  void KeyboardVisibility::update()
  {
    Inherited::update();

#if _DEBUG
    if (m_visibilityKey < 0 && m_invisibilityKey < 0)
    {
      ASSERT_FAIL();
      return;
    }
#endif

    if (observer_ptr<Renderer> renderer = getGameObject().findComponent<Renderer>(); renderer != nullptr)
    {
      bool currentState = renderer->isActive();

      if (m_inputMode == InputMode::kContinuous && m_visibilityKey > 0)
      {
        if (currentState != isKeyPressed(m_visibilityKey))
        {
          getGameObject().setActive(!currentState);
        }
      }
      else
      {
        if (currentState && m_invisibilityKey > 0 && isKeyTapped(m_invisibilityKey))
        {
          getGameObject().setActive(false);
        }
        else if (!currentState && m_visibilityKey > 0 && isKeyTapped(m_visibilityKey))
        {
          getGameObject().setActive(true);
        }
      }
    }
  }
}