#include "CelesteTestUtils/Utils/InputUtils.h"
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
    mouse.update();
  }

  //------------------------------------------------------------------------------------------------
  void simulateMouseButtonPressed(Celeste::Input::MouseButton button)
  {
    Celeste::Input::Mouse& mouse = Celeste::Input::getMouse();

    mouse.setButtonPressed(button);
    mouse.update();
  }

  //------------------------------------------------------------------------------------------------
  void simulateMouseButtonClicked(Celeste::Input::MouseButton button)
  {
    Celeste::Input::Mouse& mouse = Celeste::Input::getMouse();

    mouse.setButtonReleased(button);
    mouse.update();
    mouse.setButtonPressed(button);
    mouse.update();
  }

  //------------------------------------------------------------------------------------------------
  void simulateKeyReleased(int key)
  {
    Celeste::Input::getKeyboard().setKeyReleased(key);
    Celeste::Input::getKeyboard().update();
  }

  //------------------------------------------------------------------------------------------------
  void simulateKeyPressed(int key)
  {
    Celeste::Input::getKeyboard().setKeyPressed(key);
    Celeste::Input::getKeyboard().update();
  }

  //------------------------------------------------------------------------------------------------
  void simulateKeyTapped(int key)
  {
    Celeste::Input::Keyboard& keyboard = Celeste::Input::getKeyboard();
    
    keyboard.setKeyReleased(key);
    keyboard.update();
    keyboard.setKeyPressed(key);
    keyboard.update();
  }
}