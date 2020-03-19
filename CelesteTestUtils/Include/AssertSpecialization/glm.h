#pragma once

#include "glm/glm.hpp"
#include "CppUnitTest.h"


namespace Microsoft::VisualStudio::CppUnitTestFramework
{
  template<>
  inline std::wstring ToString<glm::vec2>(const glm::vec2& vec)
  {
    std::wstring str;
    str.append(std::to_wstring(vec.x));
    str.append(L", ");
    str.append(std::to_wstring(vec.y));

    return str;
  }

  template<>
  inline std::wstring ToString<glm::uvec2>(const glm::uvec2& vec)
  {
    std::wstring str;
    str.append(std::to_wstring(vec.x));
    str.append(L", ");
    str.append(std::to_wstring(vec.y));

    return str;
  }

  template<>
  inline std::wstring ToString<glm::vec3>(const glm::vec3& vec)
  {
    std::wstring str;
    str.append(std::to_wstring(vec.x));
    str.append(L", ");
    str.append(std::to_wstring(vec.y));
    str.append(L", ");
    str.append(std::to_wstring(vec.z));

    return str;
  }

  template<>
  inline std::wstring ToString<glm::vec4>(const glm::vec4& vec)
  {
    std::wstring str;
    str.append(std::to_wstring(vec.x));
    str.append(L", ");
    str.append(std::to_wstring(vec.y));
    str.append(L", ");
    str.append(std::to_wstring(vec.z));
    str.append(L", ");
    str.append(std::to_wstring(vec.w));

    return str;
  }

  template<>
  inline std::wstring ToString<glm::mat4>(const glm::mat4& mat)
  {
    std::wstring str;
    str.append(ToString<glm::vec4>(mat[0]));
    str.append(L", ");
    str.append(ToString<glm::vec4>(mat[1]));
    str.append(L", ");
    str.append(ToString<glm::vec4>(mat[2]));
    str.append(L", ");
    str.append(ToString<glm::vec4>(mat[3]));

    return str;
  }
}