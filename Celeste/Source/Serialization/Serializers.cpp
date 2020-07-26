#include "Serialization/Serializers.h"
#include "Resources/2D/Texture2D.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template <>
  void serialize(bool value, std::string& output)
  {
    output.assign(value ? "true" : "false");
  }

  //------------------------------------------------------------------------------------------------
  template <>
  void serialize(const std::string& value, std::string& output)
  {
    output.assign(value.c_str());
  }

  //------------------------------------------------------------------------------------------------
  template <>
  void serialize(const Path& value, std::string& output)
  {
    output.assign(value.c_str());
  }

  //------------------------------------------------------------------------------------------------
  template <>
  void serialize(const Resources::Texture2D& value, std::string& output)
  {
    output.assign(value.getFilePath().as_string());
  }

  //------------------------------------------------------------------------------------------------
  template <>
  void serialize(Resources::Texture2D* value, std::string& output)
  {
    output.assign(value != nullptr ? value->getFilePath().as_string() : "");
  }
}