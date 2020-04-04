#include "Input/InputManager.h"
#include "Game/Game.h"
#include "Input/KeyboardActivator.h"
#include "Input/MouseInteractionHandler.h"
#include "Input/GraphicsRaycaster.h"
#include "Input/PhysicsRaycaster.h"
#include "Algorithms/EntityAlgorithms.h"
#include "Scene/SceneUtils.h"
#include "Debug/DolceUtils.h"

#include <unordered_set>


namespace Celeste::Input
{
  //------------------------------------------------------------------------------------------------
  InputManager::InputManager(GLFWwindow* window)
  {
    glfwSetKeyCallback(window, &keyCallback);
    glfwSetCharCallback(window, &charCallback);
    glfwSetMouseButtonCallback(window, &mouseButtonCallback);
  }

  //------------------------------------------------------------------------------------------------
  InputManager::~InputManager()
  {
    KeyboardActivator::m_allocator.deallocateAll();
    MouseInteractionHandler::m_allocator.deallocateAll();
    GraphicsRaycaster::m_allocator.deallocateAll();
    PhysicsRaycaster::m_allocator.deallocateAll();
  }

  //------------------------------------------------------------------------------------------------
  void InputManager::handleInput()
  {
    Inherited::handleInput();

    m_keyboard.handleInput();

    // Do this here rather than in the mouse class so that we can completely control the mouse behaviour
    // from outside the class
    updateMousePosition();
    m_mouse.handleInput();

    raycast();

    Algorithms::handleInput(KeyboardActivator::m_allocator);
    Algorithms::handleInput(MouseInteractionHandler::m_allocator);
  }

  //------------------------------------------------------------------------------------------------
  void InputManager::update(GLfloat elapsedGameTime)
  {
    Inherited::update(elapsedGameTime);

    Algorithms::update(elapsedGameTime, KeyboardActivator::m_allocator);
    Algorithms::update(elapsedGameTime, MouseInteractionHandler::m_allocator);
  }

  //------------------------------------------------------------------------------------------------
  void InputManager::updateMousePosition()
  {
    // Update mouse position
    double x = 0, y = 0;
    glfwGetCursorPos(getWindow().getGLWindow(), &x, &y);
    
    m_mouse.getTransform().setTranslation(static_cast<float>(x), getViewportDimensions().y - static_cast<float>(y));
  }

  //------------------------------------------------------------------------------------------------
  void InputManager::raycast() const
  {
    std::unordered_set<observer_ptr<GameObject>> hitGameObjects;

    for (GraphicsRaycaster& graphicsRaycaster : GraphicsRaycaster::m_allocator)
    {
      auto hitObjects = graphicsRaycaster.raycast();
      if (!hitObjects.empty())
      {
        ASSERT(hitGameObjects.find(hitObjects[0]) == hitGameObjects.end());
        hitGameObjects.emplace(hitObjects[0]);
      }
    }

    for (PhysicsRaycaster& physicsRaycaster : PhysicsRaycaster::m_allocator)
    {
      auto hitObjects = physicsRaycaster.raycast();
      if (!hitObjects.empty())
      {
        ASSERT(hitGameObjects.find(hitObjects[0]) == hitGameObjects.end());
        hitGameObjects.emplace(hitObjects[0]);
      }
    }

    for (MouseInteractionHandler& mouseInteractionhandler : MouseInteractionHandler::m_allocator)
    {
      mouseInteractionhandler.setMouseOver(hitGameObjects.find(mouseInteractionhandler.getGameObject()) != hitGameObjects.end());
    }
  }

  //------------------------------------------------------------------------------------------------
  void keyCallback(GLFWwindow* /*window*/, int key, int /*scancode*/, int action, int /*modifiers*/)
  {
#if _DEBUG
    if (Debug::getDolce().hasKeyboardFocus())
    {
      return;
    }
#endif

    // This callback is called when the keyboard state CHANGES

    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
      getKeyboard().setKeyPressed(key);
    }
    else if (action == GLFW_RELEASE)
    {
      getKeyboard().setKeyReleased(key);
    }
  }

  //------------------------------------------------------------------------------------------------
  void charCallback(GLFWwindow* /*window*/, unsigned int codepoint)
  {
#if _DEBUG
    if (Debug::getDolce().hasKeyboardFocus())
    {
      return;
    }
#endif

    getKeyboard().onTextInputted(static_cast<char>(codepoint));
  }

  //------------------------------------------------------------------------------------------------
  void mouseButtonCallback(GLFWwindow* /*window*/, int button, int action, int /*mods*/)
  {
#if _DEBUG
    if (Debug::getDolce().hasMouseFocus())
    {
      return;
    }
#endif

    // This callback is called when the mouse state CHANGES

    MouseButton mButton = MouseButton::kLeft;
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
      mButton = MouseButton::kLeft;
    }
    else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
    {
      mButton = MouseButton::kMiddle;
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
      mButton = MouseButton::kRight;
    }
    else
    {
      ASSERT_FAIL();
      return;
    }

    if (action == GLFW_PRESS)
    {
      getMouse().setButtonPressed(mButton);
    }
    else if (action == GLFW_RELEASE)
    {
      getMouse().setButtonReleased(mButton);
    }
    else
    {
      ASSERT_FAIL();
    }
  }
}