#pragma once

#include <type_traits>


namespace Celeste
{
  template <class T>
  struct is_managed_component : std::integral_constant<bool, T::isManaged()> {};
}