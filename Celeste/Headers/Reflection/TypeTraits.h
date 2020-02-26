#pragma once

#include "Templates/ctstring.h"


namespace Celeste
{
  namespace Reflection
  {
    //------------------------------------------------------------------------------------------------
    template <typename T>
    constexpr bool is_type_in_namespace(const ctstring name)
    {
#if defined(_MSC_VER)
#define PRETTY_FUNCTION_OFFSET_1 \
  (sizeof("void __cdecl Celeste::Reflection::is_type_in_namespace<struct ") - 1)
#define PRETTY_FUNCTION_OFFSET_2 \
  (sizeof("void __cdecl Celeste::Reflection::is_type_in_namespace<class ") - 1)

      return ctstring(__FUNCSIG__ + PRETTY_FUNCTION_OFFSET_1).begins_with(name) ||
             ctstring(__FUNCSIG__ + PRETTY_FUNCTION_OFFSET_2).begins_with(name);

#undef PRETTY_FUNCTION_OFFSET_1
#undef PRETTY_FUNCTION_OFFSET_2
#elif defined(__clang__)
      return ctstring(__PRETTY_FUNCTION__ +
        (sizeof("bool Celeste::Reflection::is_type_in_namespace(const "
          "Celeste::ctstring) [T = ") -
          1))
        .begins_with(name);
#elif defined(__GNUC__)
      return ctstring(__PRETTY_FUNCTION__ +
        (sizeof("constexpr bool "
          "Celeste::Reflection::is_type_in_namespace(Celeste::ctstring) "
          "[with T = ") -
          1))
        .begins_with(name);
#else
#error "Your compiler is not supported, yet."
#endif
    }
  }
}