#pragma once

#include "Serialization/Serializers.h"
#include "glm/glm.hpp"
#include "Maths/MathsEnums.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template <>
  CelesteDllExport void serialize(const glm::vec2& value, std::string& output);

  //------------------------------------------------------------------------------------------------
  template <>
  CelesteDllExport void serialize(const glm::uvec2& value, std::string& output);

  //------------------------------------------------------------------------------------------------
  template <>
  CelesteDllExport void serialize(const glm::vec3& value, std::string& output);

  //------------------------------------------------------------------------------------------------
  template <>
  CelesteDllExport void serialize(const glm::vec4& value, std::string& output);
}