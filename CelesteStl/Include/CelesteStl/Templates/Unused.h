#pragma once

namespace celstl
{
  //------------------------------------------------------------------------------------------------
  template <class... ArgTypes>
  void unused(ArgTypes&&...) noexcept { }
}