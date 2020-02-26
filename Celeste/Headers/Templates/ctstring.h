#pragma once

#include <utility>
#include <type_traits>


namespace Celeste
{
  class ctstring
  {
    public:
      constexpr ctstring(const char* string) : 
        m_string(string)
      {
      }

      constexpr const char* c_str() const { return m_string; }

      constexpr bool begins_with(const ctstring other) const
      {
        return !*other.c_str() ||
          (*m_string && *m_string == *other.c_str() &&
          ctstring(m_string + 1).begins_with(other.c_str() + 1));
      }

    private:
      const char* m_string;
  };
}