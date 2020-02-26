#pragma once

#include "Objects/GameObject.h"
#include "sol.hpp"


namespace CelesteTestUtils
{
  class MockGameObject : public Celeste::GameObject
  {
    public:
      MockGameObject() = default;
      ~MockGameObject() = default;

      size_t component_count_Public() const { return component_count(); }
      size_t script_count_Public() const { return script_count(); }
  };
}

namespace sol
{
  namespace detail
  {
    template <>
    struct is_container<CelesteTestUtils::MockGameObject> : std::false_type { };
  }
}