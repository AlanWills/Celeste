#include "Serialization/MathsSerializers.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template <>
  void serialize(const glm::vec2& value, std::string& output)
  {
    output.assign(std::to_string(value.x));
    output.push_back(',');
    output.append(std::to_string(value.y));
  }

  //------------------------------------------------------------------------------------------------
  template <>
  void serialize(const glm::uvec2& value, std::string& output)
  {
    output.assign(std::to_string(value.x));
    output.push_back(',');
    output.append(std::to_string(value.y));
  }

  //------------------------------------------------------------------------------------------------
  template <>
  void serialize(const glm::vec3& value, std::string& output)
  {
    output.assign(std::to_string(value.x));
    output.push_back(',');
    output.append(std::to_string(value.y));
    output.push_back(',');
    output.append(std::to_string(value.z));
  }

  //------------------------------------------------------------------------------------------------
  template <>
  void serialize(const glm::vec4& value, std::string& output)
  {
    output.assign(std::to_string(value.x));
    output.push_back(',');
    output.append(std::to_string(value.y));
    output.push_back(',');
    output.append(std::to_string(value.z));
    output.push_back(',');
    output.append(std::to_string(value.w));
  }
}