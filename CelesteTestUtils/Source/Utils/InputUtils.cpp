#include "Utils/InputUtils.h"
#include "Input/Mouse.h"
#include "Input/Keyboard.h"
#include "Input/InputUtils.h"


namespace CelesteTestUtils
{
  //------------------------------------------------------------------------------------------------
  void simulateMouseButtonReleased(Celeste::Input::MouseButton button)
  {
    Celeste::Input::Mouse& mouse = Celeste::Input::getMouse();

    mouse.setButtonReleased(button);
    mouse.handleInput();
  }

  //------------------------------------------------------------------------------------------------
  void simulateMouseButtonPressed(Celeste::Input::MouseButton button)
  {
    Celeste::Input::Mouse& mouse = Celeste::Input::getMouse();

    mouse.setButtonPressed(button);
    mouse.handleInput();
  }

  //------------------------------------------------------------------------------------------------
  void simulateMouseButtonClicked(Celeste::Input::MouseButton button)
  {
    Celeste::Input::Mouse& mouse = Celeste::Input::getMouse();

    mouse.setButtonReleased(button);
    mouse.handleInput();
    mouse.setButtonPressed(button);
    mouse.handleInput();
  }

  //------------------------------------------------------------------------------------------------
  void simulateKeyReleased(int key)
  {
    Celeste::Input::getKeyboard().setKeyReleased(key);
    Celeste::Input::getKeyboard().handleInput();
  }

  //------------------------------------------------------------------------------------------------
  void simulateKeyPressed(int key)
  {
    Celeste::Input::getKeyboard().setKeyPressed(key);
    Celeste::Input::getKeyboard().handleInput();
  }

  //------------------------------------------------------------------------------------------------
  void simulateKeyTapped(int key)
  {
    Celeste::Input::Keyboard& keyboard = Celeste::Input::getKeyboard();
    
    keyboard.setKeyReleased(key);
    keyboard.handleInput();
    keyboard.setKeyPressed(key);
    keyboard.handleInput();
  }
}