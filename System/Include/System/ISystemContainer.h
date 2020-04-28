#pragma once

#include <memory>


namespace Celeste::System
{
  class ISystem;

  class ISystemContainer
  {
    public:
      virtual ~ISystemContainer() = default;

      virtual void addSystem(size_t id, std::unique_ptr<ISystem>&& system) = 0;
      virtual void removeSystem(size_t id) = 0;
      virtual ISystem* getSystem(size_t id) = 0;
  };
}