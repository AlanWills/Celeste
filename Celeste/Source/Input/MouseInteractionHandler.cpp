#include "Input/MouseInteractionHandler.h"
#include "Input/InputManager.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace Celeste::Input
{
  REGISTER_COMPONENT(MouseInteractionHandler, 10)

  //------------------------------------------------------------------------------------------------
  MouseInteractionHandler::MouseInteractionHandler(GameObject& gameObject) :
    Inherited(gameObject),
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
  void MouseInteractionHandler::handleInput()
  {
    Inherited::handleInput();

    const Mouse& mouse = getMouse();
    bool leftMouseButtonPressed = mouse.isButtonPressed(MouseButton::kLeft);
    bool middleMouseButtonPressed = mouse.isButtonPressed(MouseButton::kMiddle);
    bool rightMouseButtonPressed = mouse.isButtonPressed(MouseButton::kRight);

    if (m_isMouseOver)
    {
      GameObject& gameObject = *getGameObject();

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

    m_mouseButtonPressed[0] = leftMouseButtonPressed;
    m_mouseButtonPressed[1] = middleMouseButtonPressed;
    m_mouseButtonPressed[2] = rightMouseButtonPressed;
  }

  //------------------------------------------------------------------------------------------------
  void MouseInteractionHandler::setMouseOver(bool mouseOver)
  {
    if (mouseOver == m_isMouseOver)
    {
      // Early exit
      return;
    }

    if (!m_isMouseOver)
    {
      m_onEnter.invoke(*getGameObject());
      m_isMouseOver = true;
    }
    else
    {
      m_onLeave.invoke(*getGameObject());
      m_isMouseOver = false;
    }
  }
}