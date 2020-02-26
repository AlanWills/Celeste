#pragma once

#include "Deserializers.h"
#include "Maths/MathsEnums.h"

#include <string>


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport bool deserialize<glm::vec2>(const std::string& text, glm::vec2& output);

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport bool deserialize<glm::uvec2>(const std::string& text, glm::uvec2& output);

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport bool deserialize<glm::vec3>(const std::string& text, glm::vec3& output);

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport bool deserialize<glm::vec4>(const std::string& text, glm::vec4& output);

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport bool deserialize<Maths::Space>(const std::string& text, Maths::Space& output);
}