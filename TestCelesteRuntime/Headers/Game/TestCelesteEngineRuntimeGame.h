#pragma once

#include "Game/Game.h"


namespace TestCelesteRuntime
{
  class TestCelesteRuntimeGame : public Celeste::Game
  {
    protected:
      void onInitialize() override;

    private:
      using Inherited = Celeste::Game;
  };
}