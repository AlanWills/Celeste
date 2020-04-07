#pragma once

#include "Assert/Assert.h"
#include "TypeTraits.h"
#include "ITypeInfo.h"

#include <string>
#include <typeinfo>


namespace Celeste
{
  namespace Reflection
  {
    template <typename T>
    class Type : public ITypeInfo
    {
      public:
        Type() :
          m_name(),
          m_assembly(),
          m_namespace()
        {
          // __cdecl Celeste::Reflection::Type<class Celeste::Animation>::Type(void)
          size_t offset = sizeof("__cdecl Celeste::Reflection::Type<") - 1;
          const char* fsig = __FUNCSIG__;
          bool isClass = *(fsig + offset) == 'c';
          size_t removalIndex = (isClass ? sizeof("class ") : sizeof("struct ")) - 1; // -1 because of ending delimiter \0
          const char* startingChar = fsig + offset + removalIndex;
          const char* closingChar = strchr(startingChar, '>');
          const char* firstColon = strchr(startingChar, ':');
          const char* lastColon = firstColon + 1;

          // Constructor will also add ::Type(void) after closing char so we iterate until we get to a colon before the closing char
          const char* temp = strchr(lastColon, ':');
          while (temp < closingChar)
          {
            lastColon = temp;
            temp = strchr(++lastColon, ':');
          }

          m_name.assign(lastColon, closingChar - lastColon);
          m_assembly.assign(startingChar, firstColon);
          m_namespace.assign(startingChar, lastColon - 2); // Don't write the final '::'
        }

        const std::string& getName() const override { return m_name; }
        const std::string& getAssembly() const override { return m_assembly; }
        const std::string& getNamespace() const override { return m_namespace; }

        constexpr bool isInNamespace(const ctstring namespaceName) const { return is_type_in_namespace<T>(namespaceName); }
        bool isInNamespace(const std::string& namespaceName) const { return m_namespace.compare(0, namespaceName.size(), namespaceName) == 0; }

      private:
        std::string m_name;
        std::string m_assembly;
        std::string m_namespace;
    };

    //------------------------------------------------------------------------------------------------
    template <>
    class Type<int> : public ITypeInfo
    {
      public:
        Type() :
          m_name("int"),
          m_assembly(),
          m_namespace() { }

        const std::string& getName() const override { return m_name; }
        const std::string& getAssembly() const override { return m_assembly; }
        const std::string& getNamespace() const override { return m_namespace; }

      private:
        std::string m_name;
        std::string m_assembly;
        std::string m_namespace;
    };

    //------------------------------------------------------------------------------------------------
    template <>
    class Type<float> : public ITypeInfo
    {
      public:
        Type() :
          m_name("float"),
          m_assembly(),
          m_namespace() { }

        const std::string& getName() const override { return m_name; }
        const std::string& getAssembly() const override { return m_assembly; }
        const std::string& getNamespace() const override { return m_namespace; }

      private:
        std::string m_name;
        std::string m_assembly;
        std::string m_namespace;
    };

    //------------------------------------------------------------------------------------------------
    template <>
    class Type<std::string> : public ITypeInfo
    {
      public:
        Type() :
          m_name("string"),
          m_assembly(),
          m_namespace() { }

        const std::string& getName() const override { return m_name; }
        const std::string& getAssembly() const override { return m_assembly; }
        const std::string& getNamespace() const override { return m_namespace; }

      private:
        std::string m_name;
        std::string m_assembly;
        std::string m_namespace;
    };
  }
}