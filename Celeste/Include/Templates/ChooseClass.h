#pragma once


namespace Celeste
{
  template <bool var, class is_true, class is_false>
  struct choose_class { };

  template <class is_true, class is_false>
  struct choose_class<true, is_true, is_false> { using type = is_true; };

  template <class is_true, class is_false>
  struct choose_class<false, is_true, is_false> { using type = is_false; };
}