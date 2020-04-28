#pragma once


namespace Celeste::System
{
  class ISystem
  {
    public:
      virtual ~ISystem() = default;

      virtual void handleInput() = 0;
      virtual void update(float elapsedGameTime) = 0;
  };
}