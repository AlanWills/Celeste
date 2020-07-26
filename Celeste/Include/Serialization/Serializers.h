#pragma once

#include "Utils/ToString.h"
#include "FileSystem/Path.h"

#include <string>
#include <vector>


namespace Celeste
{
  namespace Resources
  {
    class Texture2D;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void serialize(T value, std::string& output)
  {
    output.assign(Celeste::to_string<T>(value));
  }

  //------------------------------------------------------------------------------------------------
  template <>
  CelesteDllExport void serialize(bool value, std::string& output);

  //------------------------------------------------------------------------------------------------
  template <>
  CelesteDllExport void serialize(const std::string& value, std::string& output);

  //------------------------------------------------------------------------------------------------
  template <>
  CelesteDllExport void serialize(const Path& value, std::string& output);

  //------------------------------------------------------------------------------------------------
  template <>
  CelesteDllExport void serialize(const Resources::Texture2D& value, std::string& output);

  //------------------------------------------------------------------------------------------------
  template <>
  CelesteDllExport void serialize(Resources::Texture2D* value, std::string& output);
}