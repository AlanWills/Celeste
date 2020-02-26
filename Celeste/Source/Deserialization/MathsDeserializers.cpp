#include "Deserialization/MathsDeserializers.h"
#include "Debug/Assert.h"

#include <algorithm>


namespace Celeste
{
  namespace glm_vec_internals
  {
    enum class ValueType
    {
      kAbsolute,
      kRelative
    };

    //------------------------------------------------------------------------------------------------
    ValueType formatValueType(std::string& str)
    {
      if (str.find_first_of('%') < str.size())
      {
        str.erase(std::remove(str.begin(), str.end(), '%'), str.end());
        return ValueType::kRelative;
      }

      return ValueType::kAbsolute;
    }

    //------------------------------------------------------------------------------------------------
    bool tryConvertToFloat(std::string& str, float& output, float viewportDimension)
    {
      ValueType valueType = formatValueType(str);

      char* e;
      errno = 0;
      float f = std::strtof(str.c_str(), &e);

      if (errno != 0 ||  // error, overflow or underflow
        *e != '\0')    // error, we didn't consume the entire string
      {
        return false;
      }

      output = valueType == ValueType::kAbsolute ? f : f * viewportDimension;
      return true;
    }

    //------------------------------------------------------------------------------------------------
    bool tryConvertToUInt(std::string& str, glm::uint& output, float viewportDimension)
    {
      ValueType valueType = formatValueType(str);

      char* e;
      errno = 0;
      glm::uint f = static_cast<glm::uint>(std::strtoul(str.c_str(), &e, 10));

      if (errno != 0 ||  // error, overflow or underflow
        *e != '\0')    // error, we didn't consume the entire string
      {
        return false;
      }

      output = valueType == ValueType::kAbsolute ? f : f * static_cast<glm::uint>(viewportDimension);
      return true;
    }
  }

  //------------------------------------------------------------------------------------------------
  template <>
  bool deserialize<glm::vec2>(const std::string& text, glm::vec2& output)
  {
    if (text.empty())
    {
      ASSERT_FAIL();
      return false;
    }

    // Do not wish to apply changes unless whole conversion was a success
    glm::vec2 temp;
    const glm::vec2& viewportDimensions = getViewportDimensions();
    std::string str(text);

    size_t delimiterIndex = str.find_first_of(',');
    if (!glm_vec_internals::tryConvertToFloat(str.substr(0, delimiterIndex), temp.x, viewportDimensions.x))
    {
      ASSERT_FAIL();
      return false;
    }

    if (delimiterIndex >= str.size())
    {
      output.x = temp.x;
      return true;
    }

    str = str.substr(delimiterIndex + 1);
    delimiterIndex = str.find_first_of(',');
    if (!glm_vec_internals::tryConvertToFloat(str.substr(0, delimiterIndex), temp.y, viewportDimensions.y))
    {
      ASSERT_FAIL();
      return false;
    }

    output = temp;
    return true;
  }
  //------------------------------------------------------------------------------------------------
  template <>
  bool deserialize<glm::uvec2>(const std::string& text, glm::uvec2& output)
  {
    if (text.empty())
    {
      ASSERT_FAIL();
      return false;
    }

    // Do not wish to apply changes unless whole conversion was a success
    glm::uvec2 temp;
    const glm::vec2& viewportDimensions = getViewportDimensions();
    std::string str(text);

    size_t delimiterIndex = str.find_first_of(',');
    if (!glm_vec_internals::tryConvertToUInt(str.substr(0, delimiterIndex), temp.x, viewportDimensions.x))
    {
      ASSERT_FAIL();
      return false;
    }

    if (delimiterIndex >= str.size())
    {
      output.x = temp.x;
      return true;
    }

    str = str.substr(delimiterIndex + 1);
    delimiterIndex = str.find_first_of(',');
    if (!glm_vec_internals::tryConvertToUInt(str.substr(0, delimiterIndex), temp.y, viewportDimensions.y))
    {
      ASSERT_FAIL();
      return false;
    }

    output = temp;
    return true;
  }

  //------------------------------------------------------------------------------------------------
  template <>
  bool deserialize<glm::vec3>(const std::string& text, glm::vec3& output)
  {
    if (text.empty())
    {
      ASSERT_FAIL();
      return false;
    }

    // Do not wish to apply changes unless whole conversion was a success
    glm::vec3 temp;
    const glm::vec2& viewportDimensions = getViewportDimensions();
    std::string str(text);

    size_t delimiterIndex = str.find_first_of(',');
    if (!glm_vec_internals::tryConvertToFloat(str.substr(0, delimiterIndex), temp.x, viewportDimensions.x))
    {
      ASSERT_FAIL();
      return false;
    }

    if (delimiterIndex >= str.size())
    {
      output.x = temp.x;
      return true;
    }

    str = str.substr(delimiterIndex + 1);
    delimiterIndex = str.find_first_of(',');

    if (!glm_vec_internals::tryConvertToFloat(str.substr(0, delimiterIndex), temp.y, viewportDimensions.y))
    {
      ASSERT_FAIL();
      return false;
    }

    if (delimiterIndex >= str.size())
    {
      output.x = temp.x;
      output.y = temp.y;
      return true;
    }

    str = str.substr(delimiterIndex + 1);
    delimiterIndex = str.find_first_of(',');

    if (!glm_vec_internals::tryConvertToFloat(str.substr(0, delimiterIndex), temp.z, 1))
    {
      ASSERT_FAIL();
      return false;
    }

    output = temp;
    return true;
  }

  //------------------------------------------------------------------------------------------------
  template <>
  bool deserialize<glm::vec4>(const std::string& text, glm::vec4& output)
  {
    if (text.empty())
    {
      ASSERT_FAIL();
      return false;
    }

    glm::vec4 temp;
    const glm::vec2& viewportDimensions = getViewportDimensions();
    std::string str(text);

    size_t delimiterIndex = str.find_first_of(',');
    if (!glm_vec_internals::tryConvertToFloat(str.substr(0, delimiterIndex), temp.x, viewportDimensions.x))
    {
      ASSERT_FAIL();
      return false;
    }

    if (delimiterIndex >= str.size())
    {
      output.x = temp.x;
      return true;
    }

    str = str.substr(delimiterIndex + 1);
    delimiterIndex = str.find_first_of(',');

    if (!glm_vec_internals::tryConvertToFloat(str.substr(0, delimiterIndex), temp.y, viewportDimensions.y))
    {
      ASSERT_FAIL();
      return false;
    }

    if (delimiterIndex >= str.size())
    {
      output.x = temp.x;
      output.y = temp.y;
      return true;
    }

    str = str.substr(delimiterIndex + 1);
    delimiterIndex = str.find_first_of(',');

    if (!glm_vec_internals::tryConvertToFloat(str.substr(0, delimiterIndex), temp.z, 1))
    {
      ASSERT_FAIL();
      return false;
    }

    if (delimiterIndex >= str.size())
    {
      output.x = temp.x;
      output.y = temp.y;
      output.z = temp.z;
      return true;
    }

    str = str.substr(delimiterIndex + 1);
    delimiterIndex = str.find_first_of(',');

    if (!glm_vec_internals::tryConvertToFloat(str.substr(0, delimiterIndex), temp.w, 1))
    {
      ASSERT_FAIL();
      return false;
    }

    output = temp;
    return true;
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