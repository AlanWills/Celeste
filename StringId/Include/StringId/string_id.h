#pragma once

#include "StringId/fvn_hash.h"

#include <cstring>
#include <string>
#include <string_view>
#include <memory>


class string_id
{
  public:
    using hash_type = fvn::hash_type;

    explicit string_id()
      : string_id("")
    {
    }

    explicit string_id(hash_type hash)
      : m_id(hash)
#if _DEBUG
      , m_debugStringLength(1)
      , m_debugString()
#endif
    {
#if _DEBUG
      m_debugString = new char[m_debugStringLength] { 0 };
#endif
    }

    explicit string_id(const char* str)
      : m_id(fvn::hash(str))
#if _DEBUG
      , m_debugStringLength(strlen(str) + 1)
      , m_debugString()
#endif
    {
#if _DEBUG
      m_debugString = new char[m_debugStringLength];
      strncpy_s(m_debugString, m_debugStringLength, str, m_debugStringLength);
#endif
    }

    explicit string_id(const std::string& str)
      : string_id(str.c_str())
    {
    }

    explicit string_id(std::string&& str)
      : string_id(str.c_str())
    {
    }

    explicit string_id(std::string_view str)
      : string_id(str.data())
    {
    }

    string_id(const string_id& stringId)
      : m_id(stringId.m_id)
#if _DEBUG
      , m_debugStringLength(stringId.m_debugStringLength)
      , m_debugString()
#endif
    {
#if _DEBUG
      m_debugString = new char[m_debugStringLength];
      strncpy_s(m_debugString, m_debugStringLength, stringId.debug_string(), m_debugStringLength);
#endif
    }

    string_id(string_id&& stringId) noexcept
      : m_id(stringId.m_id)
#if _DEBUG
      , m_debugStringLength(stringId.m_debugStringLength)
      , m_debugString(stringId.m_debugString)
#endif
    {
#if _DEBUG
      stringId.m_debugString = nullptr;
#endif
    }

#if _DEBUG
    ~string_id()
    {
      delete[] m_debugString;
    }
#else
    ~string_id() = default;
#endif

    string_id& operator=(const string_id& stringId) = delete;
    string_id& operator=(string_id&& stringId) noexcept
    {
      m_id = stringId.m_id;
#if _DEBUG
      m_debugStringLength = stringId.m_debugStringLength;
      m_debugString = stringId.m_debugString;
      stringId.m_debugString = nullptr;
#endif
      return *this;
    }

    hash_type id() const noexcept { return m_id; }

#if _DEBUG
    const char* const debug_string() const noexcept { return m_debugString; }
#endif

    friend bool operator==(const string_id& a, const string_id& b) noexcept { return a.m_id == b.m_id; }
    friend bool operator==(hash_type a, const string_id& b) noexcept { return a == b.m_id; }
    friend bool operator==(const string_id& a, hash_type b) noexcept { return a.m_id == b; }
    friend bool operator==(const char* a, const string_id& b) noexcept { return fvn::hash(a) == b.m_id; }
    friend bool operator==(const string_id& a, const char* b) noexcept { return a.m_id == fvn::hash(b); }
    friend bool operator==(const std::string& a, const string_id& b) noexcept { return fvn::hash(a.c_str()) == b.m_id; }
    friend bool operator==(const string_id& a, const std::string& b) noexcept { return a.m_id == fvn::hash(b.c_str()); }
    friend bool operator==(std::string_view a, const string_id& b) noexcept { return fvn::hash(a.data()) == b.m_id; }
    friend bool operator==(const string_id& a, std::string_view b) noexcept { return a.m_id == fvn::hash(b.data()); }

    friend bool operator!=(const string_id& a, const string_id& b) noexcept { return !(a == b); }
    friend bool operator!=(hash_type a, const string_id& b) noexcept { return !(a == b); }
    friend bool operator!=(const string_id& a, hash_type b) noexcept { return !(a == b); }
    friend bool operator!=(const char* a, const string_id& b) noexcept { return !(a == b); }
    friend bool operator!=(const string_id& a, const char* b) noexcept { return !(a == b); }
    friend bool operator!=(const std::string& a, const string_id& b) noexcept { return !(a == b); }
    friend bool operator!=(const string_id& a, const std::string& b) noexcept { return !(a == b); }
    friend bool operator!=(std::string_view a, const string_id& b) noexcept { return !(a == b); }
    friend bool operator!=(const string_id& a, std::string_view b) noexcept { return !(a == b); }

  private:
    hash_type m_id;

#if _DEBUG
    size_t m_debugStringLength;
    char* m_debugString;
#endif
};

namespace std
{
  /// \brief \c std::hash support for \ref string_id.
  template <>
  struct hash<string_id>
  {
    using argument_type = string_id;
    using result_type = size_t;

    result_type operator()(const argument_type& arg) const noexcept
    {
      return static_cast<result_type>(arg.id());
    }
  };
} // namspace std