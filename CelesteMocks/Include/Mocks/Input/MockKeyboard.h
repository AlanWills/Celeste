#pragma once

#include "Input/Keyboard.h"


namespace CelesteMocks
{
  class MockKeyboard : public Celeste::Input::Keyboard
  {
    public:
      GLboolean getLatestKeyState(int key) { return getLatestKeys()[key]; }
  };
}