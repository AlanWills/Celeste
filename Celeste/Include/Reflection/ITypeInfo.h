#pragma once

#include <string>


namespace Celeste::Reflection
{
  class ITypeInfo
  {
    public:
      virtual ~ITypeInfo() = default;

      virtual const std::string& getName() const = 0;
      virtual const std::string& getAssembly() const = 0;
      virtual const std::string& getNamespace() const = 0;
  };
}