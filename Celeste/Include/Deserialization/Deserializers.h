#pragma once

#include "CelesteDllExport.h"
#include "FileSystem/Path.h"
#include "Utils/ToString.h"

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
  bool deserialize(const std::string& text, T& output)
  {
    return Celeste::from_string<T>(text, output);
  }

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport bool deserialize<std::string>(const std::string& text, std::string& output);

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport bool deserialize<Path>(const std::string& text, Path& output);

  //------------------------------------------------------------------------------------------------
  template<> 
  CelesteDllExport bool deserialize<int>(const std::string& text, int& output);

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport bool deserialize<unsigned int>(const std::string& text, unsigned int& output);

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport bool deserialize<size_t>(const std::string& text, size_t& output);

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport bool deserialize<float>(const std::string& text, float& output);

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport bool deserialize<bool>(const std::string& text, bool& output);

  //------------------------------------------------------------------------------------------------
  template<>
  CelesteDllExport bool deserialize<Resources::Texture2D*>(const std::string& text, Resources::Texture2D*& output);

  //------------------------------------------------------------------------------------------------
  template <>
  CelesteDllExport bool deserialize(const std::string& text, std::vector<Resources::Texture2D>& output);
}