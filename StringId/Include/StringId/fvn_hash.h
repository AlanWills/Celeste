#pragma once

#include <cstdint>
#include <string_view>


namespace fvn
{
  using hash_type = std::uint64_t;

  constexpr hash_type fnv_basis = 14695981039346656037ull;
  constexpr hash_type fnv_prime = 1099511628211ull;

  // FNV-1a 64 bit hash
  constexpr hash_type hash(const char* str, hash_type basis = fnv_basis)
  {
    return *str ? hash(str + 1, (basis ^ *str) * fnv_prime) : basis;
  }
}
