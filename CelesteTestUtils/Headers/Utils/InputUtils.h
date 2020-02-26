#pragma once

#include "Input/InputEnums.h"


namespace CelesteTestUtils
{
  void simulateMouseButtonReleased(Celeste::Input::MouseButton button);
  void simulateMouseButtonPressed(Celeste::Input::MouseButton button);
  void simulateMouseButtonClicked(Celeste::Input::MouseButton button);
    
  void simulateKeyReleased(int key);
  void simulateKeyPressed(int key);
  void simulateKeyTapped(int key);
}