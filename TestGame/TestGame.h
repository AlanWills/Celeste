#pragma once

#include "Game/Game.h"


namespace Celeste
{
  class TestGame : public Game 
  {
    public:
      TestGame();

    protected:
      void onInitialize() override;
      void onInitializeDolce(Dolce::IDolce& dolce) override;

    private:
      using Inherited = Game;
  };
}