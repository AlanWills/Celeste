#include "Deserialization/Deserializers.h"
#include "Resources/ResourceUtils.h"
#include "Resources/ResourceManager.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template <>
  bool deserialize<std::string>(const std::string& text, std::string& output)
  {
    output.assign(text);
    return true;
  }

  //------------------------------------------------------------------------------------------------
  template <>
  bool deserialize<Path>(const std::string& text, Path& output)
  {
    output.reset(text);
    return true;
  }

  //------------------------------------------------------------------------------------------------
  template <>
  bool deserialize<int>(const std::string& text, int& output)
  {
    if (text.empty())
    {
      ASSERT_FAIL();
      return false;
    }

    char* end = nullptr;
    long result = std::strtol(text.c_str(), &end, 10);

    if (end == nullptr || end != (text.data() + text.size()))
    {
      ASSERT_FAIL();
      return false;
    }

    output = static_cast<int>(result);
    return true;
  }

  //------------------------------------------------------------------------------------------------
  template <>
  bool deserialize<unsigned int>(const std::string& text, unsigned int& output)
  {
    if (text.empty())
    {
      ASSERT_FAIL();
      return false;
    }

    char* end = nullptr;
    long result = std::strtol(text.c_str(), &end, 10);

    if (end == nullptr || 
        end != (text.data() + text.size()) ||
        result < 0)
    {
      ASSERT_FAIL();
      return false;
    }

    output = static_cast<unsigned int>(result);
    return true;
  }

  //------------------------------------------------------------------------------------------------
  template <>
  bool deserialize<size_t>(const std::string& text, size_t& output)
  {
    if (text.empty())
    {
      ASSERT_FAIL();
      return false;
    }

    char* end = nullptr;
    long result = std::strtol(text.c_str(), &end, 10);

    if (end == nullptr || end != (text.data() + text.size()))
    {
      ASSERT_FAIL();
      return false;
    }

    output = static_cast<size_t>(result);
    return true;
  }

  //------------------------------------------------------------------------------------------------
  template <>
  bool deserialize<float>(const std::string& text, float& output)
  {
    if (text.empty())
    {
      ASSERT_FAIL();
      return false;
    }

    char* end = nullptr;
    float result = std::strtof(text.c_str(), &end);

    if (end == nullptr || end != (text.c_str() + text.size()))
    {
      ASSERT_FAIL();
      return false;
    }

    output = result;
    return true;
  }

  //------------------------------------------------------------------------------------------------
  template <>
  bool deserialize<bool>(const std::string& text, bool& output)
  {
    if (text.empty())
    {
      ASSERT_FAIL();
      return false;
    }

    if (text == "true" || text == "True")
    {
      output = true;
      return true;
    }
    else if (text == "false" || text == "False")
    {
      output = false;
      return true;
    }

    return false;
  }

  //------------------------------------------------------------------------------------------------
  template<>
  bool deserialize<Resources::Texture2D*>(const std::string& text, Resources::Texture2D*& output)
  {
    output = Resources::getResourceManager().load<Resources::Texture2D>(text);
    return true;
  }

  //------------------------------------------------------------------------------------------------
  template<>
  bool deserialize(const std::string& text, std::vector<Resources::Texture2D>& output)
  {
	  return true;
  }
}