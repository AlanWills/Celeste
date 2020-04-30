#pragma once

#include "static_type_info.h"

#include <memory>
#include <utility>


namespace Celeste::System
{
  class ISystem;

  class ISystemContainer
  {
    public:
      ISystemContainer() = default;
      ISystemContainer(const ISystemContainer&) = delete;
      ISystemContainer(ISystemContainer&&) = default;
      virtual ~ISystemContainer() = default;

      ISystemContainer& operator=(const ISystemContainer&) = delete;
      ISystemContainer& operator=(ISystemContainer&&) = default;

      virtual void addSystem(static_type_info::TypeIndex id, std::unique_ptr<ISystem>&& system) = 0;
      virtual void removeSystem(static_type_info::TypeIndex id) = 0;
      virtual ISystem* getSystem(static_type_info::TypeIndex id) = 0;

      const ISystem* getSystem(static_type_info::TypeIndex id) const
      {
        return const_cast<ISystemContainer*>(this)->getSystem(id);
      }
  };
}