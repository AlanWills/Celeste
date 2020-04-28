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
    return static_cast<Enum> (
      static_cast<typename std::underlying_type<Enum>::type>(lhs) |
      static_cast<typename std::underlying_type<Enum>::type>(rhs)
      );
  }

  //------------------------------------------------------------------------------------------------
  template<typename Enum>
  typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
    operator &(Enum lhs, Enum rhs)
  {
    return static_cast<Enum> (
      static_cast<typename std::underlying_type<Enum>::type>(lhs) &
      static_cast<typename std::underlying_type<Enum>::type>(rhs)
      );
  }

  //------------------------------------------------------------------------------------------------
  template<typename Enum>
  typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
    operator ^(Enum lhs, Enum rhs)
  {
    return static_cast<Enum> (
      static_cast<typename std::underlying_type<Enum>::type>(lhs) ^
      static_cast<typename std::underlying_type<Enum>::type>(rhs)
      );
  }

  //------------------------------------------------------------------------------------------------
  template<typename Enum>
  typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
    operator ~(Enum rhs)
  {
    return static_cast<Enum> (
      ~static_cast<typename std::underlying_type<Enum>::type>(rhs)
      );
  }

  //------------------------------------------------------------------------------------------------
  template<typename Enum>
  typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type&
    operator |=(Enum& lhs, Enum rhs)
  {
    lhs = static_cast<Enum> (
      static_cast<typename std::underlying_type<Enum>::type>(lhs) |
      static_cast<typename std::underlying_type<Enum>::type>(rhs)
      );

    return lhs;
  }

  //------------------------------------------------------------------------------------------------
  template<typename Enum>
  typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type&
    operator &=(Enum& lhs, Enum rhs)
  {
    lhs = static_cast<Enum> (
      static_cast<typename std::underlying_type<Enum>::type>(lhs) &
      static_cast<typename std::underlying_type<Enum>::type>(rhs)
      );

    return lhs;
  }

  //------------------------------------------------------------------------------------------------
  template<typename Enum>
  typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type&
    operator ^=(Enum& lhs, Enum rhs)
  {
    lhs = static_cast<Enum> (
      static_cast<typename std::underlying_type<Enum>::type>(lhs) ^
      static_cast<typename std::underlying_type<Enum>::type>(rhs)
      );

    return lhs;
  }

  //------------------------------------------------------------------------------------------------
  template<typename Enum, typename enable = typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type>
  bool hasFlag(Enum value, Enum flag)
  {
    return (value & flag) == flag;
  }
}