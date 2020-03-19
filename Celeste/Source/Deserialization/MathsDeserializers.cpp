#include "Deserialization/MathsDeserializers.h"
#include "Debug/Assert.h"
#include "Utils/StringUtils.h"

#include <algorithm>


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template <glm::length_t length, typename T>
  bool tryDeserialize(const std::string& text, glm::vec<length, T, glm::defaultp>& output)
  {
    if (text.empty())
    {
      ASSERT_FAIL();
      return false;
    }

    // Do not wish to apply changes unless whole conversion was a success
    std::vector<std::string> components;
    split(text, components, ',');
    glm::length_t componentsSize = static_cast<glm::length_t>(components.size());
    ASSERT(componentsSize <= length); // Shouldn't have specified more components than our vector

    for (glm::length_t index = 0; index < length && index < componentsSize; ++index)
    {
      if (!deserialize(components[index], output[index]))
      {
        ASSERT_FAIL();
        return false;
      }
    }

    return true;
  }

  //------------------------------------------------------------------------------------------------
  template <>
  bool deserialize<glm::vec2>(const std::string& text, glm::vec2& output)
  {
    glm::vec2 temp;
    if (tryDeserialize(text, temp))
    {
      output = temp;
      return true;
    }

    return false;
  }

  //------------------------------------------------------------------------------------------------
  template <>
  bool deserialize<glm::uvec2>(const std::string& text, glm::uvec2& output)
  {
    glm::uvec2 temp;
    if (tryDeserialize(text, temp))
    {
      output = temp;
      return true;
    }

    return false;
  }

  //------------------------------------------------------------------------------------------------
  template <>
  bool deserialize<glm::vec3>(const std::string& text, glm::vec3& output)
  {
    glm::vec3 temp;
    if (tryDeserialize(text, temp))
    {
      output = temp;
      return true;
    }

    return false;
  }

  //------------------------------------------------------------------------------------------------
  template <>
  bool deserialize<glm::vec4>(const std::string& text, glm::vec4& output)
  {
    glm::vec4 temp;
    if (tryDeserialize(text, temp))
    {
      output = temp;
      return true;
    }

    return false;
  }

  //------------------------------------------------------------------------------------------------
  template<>
  bool deserialize<Maths::Space>(const std::string& text, Maths::Space& output)
  {
    if (text == "World")
    {
      output = Maths::Space::kWorld;
      return true;
    }
    else if (text == "Local")
    {
      output = Maths::Space::kLocal;
      return true;
    }

    ASSERT_FAIL();
    return false;
  }
}