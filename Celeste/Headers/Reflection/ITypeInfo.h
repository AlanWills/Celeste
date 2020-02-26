#pragma once

#include <string>


namespace Celeste
{
  namespace Reflection
  {
    class ITypeInfo
    {
      public:
        virtual const std::string& getName() const = 0;
        virtual const std::string& getAssembly() const = 0;
        virtual const std::string& getNamespace() const = 0;
    };
  }
}