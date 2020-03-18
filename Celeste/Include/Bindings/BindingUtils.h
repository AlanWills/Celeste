#pragma once

#include "CelesteDllExport.h"

#include <string>


namespace Celeste::Bindings
{
  /// Capitalise the first letter of each word and then remove all spaces from the string.
    /// e.g. Hello world -> HelloWorld.
  CelesteDllExport std::string displayNameToVariableName(const std::string& displayName);

  /// Capitalise the first letter and every letter that follows an underscore and then remove all underscores from the string.
  /// e.g. Hello_world -> HelloWorld.
  CelesteDllExport std::string xmlAttributeNameToVariableName(const std::string& xmlAttributeName);

  /// Capitalise the first letter and every letter that follows an underscore and then replace all underscores with a space.
  /// e.g. Hello_world -> Hello World.
  CelesteDllExport std::string xmlAttributeNameToDisplayName(const std::string& xmlAttributeName);

  /// Add a space before every capitalised letter except the first letter.
  /// e.g. HelloWorld -> Hello World.
  CelesteDllExport std::string variableNameToDisplayName(const std::string& variableName);

  /// Convert a c++ namespace to a C# namespace by replacing all instances of '::' with '.'
  CelesteDllExport std::string cppNamespaceToCsNamespace(const std::string& cppNamespace);
}