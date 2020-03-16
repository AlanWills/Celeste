#pragma once

#include "CelesteDllExport.h"
#include "InputEnums.h"


namespace Celeste::Input
{
  class InputManager;
  class Keyboard;
  class Mouse;

  //------------------------------------------------------------------------------------------------
  CelesteDllExport InputManager& getInputManager();
  CelesteDllExport Keyboard& getKeyboard();
  CelesteDllExport Mouse& getMouse();

  //------------------------------------------------------------------------------------------------
  CelesteDllExport bool isKeyTapped(int key);
  CelesteDllExport bool isKeyPressed(int key);
  CelesteDllExport bool isKeyReleased(int key);

  //------------------------------------------------------------------------------------------------
  CelesteDllExport bool isButtonClicked(MouseButton button);
  CelesteDllExport bool isButtonPressed(MouseButton button);
  CelesteDllExport bool isButtonReleased(MouseButton button);
}