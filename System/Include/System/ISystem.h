#pragma once


namespace Celeste::System
{
  class ISystem
  {
    public:
      ISystem() = default;
      ISystem(const ISystem&) = delete;
      ISystem(ISystem&&) = default;
      virtual ~ISystem() = default;

      ISystem& operator=(const ISystem&) = delete;
      ISystem& operator=(ISystem&&) = default;

      virtual void update(float elapsedGameTime) = 0;
  };
}