#include "Input/MouseInteractionHandler.h"
#include "Input/InputManager.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Physics/Collider.h"


namespace Celeste::Input
{
  REGISTER_SCRIPT(MouseInteractionHandler, 10)

  //------------------------------------------------------------------------------------------------
  MouseInteractionHandler::MouseInteractionHandler() :
    m_collider(),
    m_isMouseOver(false),
    m_mouseButtonPressed{ },
    m_onEnter(),
    m_onLeave(),
    m_onLeftButtonDown(),
    m_onLeftButtonUp(),
    m_onMiddleButtonDown(),
    m_onMiddleButtonUp(),
    m_onRightButtonDown(),
    m_onRightButtonUp()
  {
    m_mouseButtonPressed.fill(false);
  }

  //------------------------------------------------------------------------------------------------
  void MouseInteractionHandler::onSetGameObject(GameObject& gameObject)
  {
    Inherited::onSetGameObject(gameObject);

    m_collider = getGameObject()->findComponent<Physics::Collider>();
  }

  //------------------------------------------------------------------------------------------------
  void MouseInteractionHandler::handleInput()
  {
    Inherited::handleInput();

#if _DEBUG
    if (m_collider == nullptr)
    {
      // If we have no collider set up, do no collision detection
      ASSERT_FAIL();
      return;
    }
#endif

    const Mouse& mouse = getMouse();
    bool leftMouseButtonPressed = mouse.isButtonPressed(MouseButton::kLeft);
    bool middleMouseButtonPressed = mouse.isButtonPressed(MouseButton::kMiddle);
    bool rightMouseButtonPressed = mouse.isButtonPressed(MouseButton::kRight);
    bool mouseOverThisFrame = m_collider->isHitByRay();

    GameObject& gameObject = *getGameObject();

    if (mouseOverThisFrame)
    {
      if (!m_isMouseOver)
      {
        m_onEnter.invoke(gameObject);
      }

      if (leftMouseButtonPressed && !m_mouseButtonPressed[0])
      {
        m_onLeftButtonDown.invoke(gameObject);
      }
      else if (!leftMouseButtonPressed && m_mouseButtonPressed[0])
      {
        m_onLeftButtonUp.invoke(gameObject);
      }
      else if (middleMouseButtonPressed && !m_mouseButtonPressed[1])
      {
        m_onMiddleButtonDown.invoke(gameObject);
      }
      else if (!middleMouseButtonPressed && m_mouseButtonPressed[1])
      {
        m_onMiddleButtonUp.invoke(gameObject);
      }
      else if (rightMouseButtonPressed && !m_mouseButtonPressed[2])
      {
        m_onRightButtonDown.invoke(gameObject);
      }
      else if (!rightMouseButtonPressed && m_mouseButtonPressed[2])
      {
        m_onRightButtonUp.invoke(gameObject);
      }
    }
    else if (m_isMouseOver)
    {
      m_onLeave.invoke(gameObject);
    }

    m_isMouseOver = mouseOverThisFrame;
    m_mouseButtonPressed[0] = leftMouseButtonPressed;
    m_mouseButtonPressed[1] = middleMouseButtonPressed;
    m_mouseButtonPressed[2] = rightMouseButtonPressed;
  }
}