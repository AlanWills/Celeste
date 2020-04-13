#pragma once

#include <type_traits>


namespace celstl
{
  //------------------------------------------------------------------------------------------------
  template<typename Enum>
  struct EnableBitMaskOperators
  {
    static constexpr bool enable = false;
  };

  //------------------------------------------------------------------------------------------------
  template<typename Enum>
  typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
    operator |(Enum lhs, Enum rhs)
  {
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<Enum> (
      static_cast<underlying>(lhs) |
      static_cast<underlying>(rhs)
      );
  }

  //------------------------------------------------------------------------------------------------
  template<typename Enum>
  typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
    operator &(Enum lhs, Enum rhs)
  {
    return static_cast<Enum> (
      static_cast<std::underlying_type<Enum>::type>(lhs) &
      static_cast<std::underlying_type<Enum>::type>(rhs)
      );
  }

  //------------------------------------------------------------------------------------------------
  template<typename Enum>
  typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
    operator ^(Enum lhs, Enum rhs)
  {
    return static_cast<Enum> (
      static_cast<std::underlying_type<Enum>::type>(lhs) ^
      static_cast<std::underlying_type<Enum>::type>(rhs)
      );
  }

  //------------------------------------------------------------------------------------------------
  template<typename Enum>
  typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
    operator ~(Enum rhs)
  {
    return static_cast<Enum> (
      ~static_cast<std::underlying_type<Enum>::type>(rhs)
      );
  }

  //------------------------------------------------------------------------------------------------
  template<typename Enum>
  typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type&
    operator |=(Enum& lhs, Enum rhs)
  {
    lhs = static_cast<Enum> (
      static_cast<std::underlying_type<Enum>::type>(lhs) |
      static_cast<std::underlying_type<Enum>::type>(rhs)
      );

    return lhs;
  }

  //------------------------------------------------------------------------------------------------
  template<typename Enum>
  typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type&
    operator &=(Enum& lhs, Enum rhs)
  {
    lhs = static_cast<Enum> (
      static_cast<std::underlying_type<Enum>::type>(lhs) &
      static_cast<std::underlying_type<Enum>::type>(rhs)
      );

    return lhs;
  }

  //------------------------------------------------------------------------------------------------
  template<typename Enum>
  typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type&
    operator ^=(Enum& lhs, Enum rhs)
  {
    lhs = static_cast<Enum> (
      static_cast<std::underlying_type<Enum>::type>(lhs) ^
      static_cast<std::underlying_type<Enum>::type>(rhs)
      );

    return lhs;
  }

  //------------------------------------------------------------------------------------------------
  template<typename Enum, typename enable = std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type>
  bool hasFlag(Enum value, Enum flag)
  {
    return (value & flag) == flag;
  }
}