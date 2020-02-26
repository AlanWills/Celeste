#include "Input/InputUtils.h"
#include "Game/Game.h"


namespace Celeste::Input
{
  //------------------------------------------------------------------------------------------------
  InputManager& getInputManager()
  {
    return Game::getInputManager();
  }

  //------------------------------------------------------------------------------------------------
  Keyboard& getKeyboard()
  {
    return getInputManager().getKeyboard();
  }

  //------------------------------------------------------------------------------------------------
  Mouse& getMouse()
  {
    return getInputManager().getMouse();
  }

  //------------------------------------------------------------------------------------------------
  bool isKeyTapped(int key)
  {
    return getKeyboard().isKeyTapped(key);
  }

  //------------------------------------------------------------------------------------------------
  bool isKeyPressed(int key)
  {
    return getKeyboard().isKeyPressed(key);
  }

  //------------------------------------------------------------------------------------------------
  bool isKeyReleased(int key)
  {
    return getKeyboard().isKeyReleased(key);
  }

  //------------------------------------------------------------------------------------------------
  bool isButtonClicked(MouseButton button)
  {
    return getMouse().isButtonClicked(button);
  }

  //------------------------------------------------------------------------------------------------
  bool isButtonPressed(MouseButton button)
  {
    return getMouse().isButtonPressed(button);
  }

  //------------------------------------------------------------------------------------------------
  bool isButtonReleased(MouseButton button)
  {
    return getMouse().isButtonReleased(button);
  }
}