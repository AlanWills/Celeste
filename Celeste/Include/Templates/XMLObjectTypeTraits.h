#pragma once

#include <type_traits>


namespace Celeste::XML
{
  template <template<typename> class T, typename K>
  struct is_reference : std::integral_constant<bool, T<K>::isReference()> {};
}