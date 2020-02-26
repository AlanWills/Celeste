#pragma once

#include "RegistryAllocator.h"
#include "Objects/GameObject.h"


namespace Celeste
{
  template <typename T>
  class DefaultRegistryAllocator : public RegistryAllocator
  {
    public:
      observer_ptr<Component> allocate(const std::string& componentName, GameObject& gameObject) const override
      {
        return gameObject.addComponent<T>();
      }
  };
}