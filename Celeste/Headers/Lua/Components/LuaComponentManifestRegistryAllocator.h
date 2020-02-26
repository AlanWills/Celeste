#pragma once

#include "CelesteDllExport.h"
#include "Registries/RegistryAllocator.h"


namespace Celeste
{
  struct LuaComponentManifestRegistryAllocator : RegistryAllocator
  {
    public:
      CelesteDllExport observer_ptr<Component> allocate(const std::string& componentName, GameObject& gameObject) const override;
  };
}