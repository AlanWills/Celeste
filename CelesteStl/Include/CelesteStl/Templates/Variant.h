#pragma once

#include <variant>


namespace celstl
{
  //------------------------------------------------------------------------------------------------
  template<typename VariantType, typename T, std::size_t index = 0>
  constexpr std::size_t variant_index() 
  {
    if constexpr (index == std::variant_size_v<VariantType>) 
    {
      return index;
    }
    else if constexpr (std::is_same_v<std::variant_alternative_t<index, VariantType>, T>) 
    {
      return index;
    }
    else 
    {
      return variant_index<VariantType, T, index + 1>();
    }
  }

  //------------------------------------------------------------------------------------------------
  template <class VariantType, typename ReturnType, typename... Args>
  struct VariantFunctions
  {
    using Variant = VariantType;
    using Function = ReturnType(*)(Args...);

    constexpr size_t size() const { return std::variant_size<Variant>::value; }

    Function m_functions[std::variant_size<Variant>::value];
  };

  //------------------------------------------------------------------------------------------------
  template <typename VariantFunctions, size_t index, template <typename> class Functor>
  struct SetVariantFunction
  {
    static constexpr void set(VariantFunctions& variantFunctions)
    {
      variantFunctions.m_functions[index] = &Functor<typename std::variant_alternative<index, typename VariantFunctions::Variant>::type>::execute;
      SetVariantFunction<VariantFunctions, index - 1, Functor>::set(variantFunctions);
    }
  };

  //------------------------------------------------------------------------------------------------
  template <typename VariantFunctions, template <typename> class Functor>
  struct SetVariantFunction<VariantFunctions, 0, Functor>
  {
    static constexpr void set(VariantFunctions& variantFunctions)
    {
      variantFunctions.m_functions[0] = &Functor<typename std::variant_alternative<0, typename VariantFunctions::Variant>::type>::execute;
    }
  };

  //------------------------------------------------------------------------------------------------
  template <typename VariantFunctions, template <typename> class Functor>
  constexpr VariantFunctions createVariantFunctions()
  {
    VariantFunctions variantFunctions = VariantFunctions();
    SetVariantFunction<VariantFunctions, variantFunctions.size() - 1, Functor>::set(variantFunctions);

    return variantFunctions;
  }
}