#pragma once

#include "Memory/ObserverPtr.h"

#include <string>


namespace Celeste
{
  class GameObject;
  class Component;

  struct RegistryAllocator
  {
    public:
      virtual observer_ptr<Component> allocate(const std::string& componentName, GameObject& gameObject) const = 0;
  };
}