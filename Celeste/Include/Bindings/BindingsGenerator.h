#pragma once

#if _DEBUG

#include "CelesteDllExport.h"
#include "Objects/ScriptableObject.h"
#include "FileSystem/Directory.h"


namespace Celeste::Bindings
{
  // Make this a class because we need to give it access to scriptable object internals via friend
  class BindingsGenerator
  {
    public:
      CelesteDllExport static void generateScriptableObjectBindings(
        const Directory& parentDirectory,
        const Reflection::ITypeInfo& typeInfo,
        const ScriptableObject& scriptableObject);

      CelesteDllExport static void generateComponentBindings(const Directory& parentDirectory, const Reflection::ITypeInfo& componentTypeInfo);

      template <typename T>
      static void generateScriptableObjectBindings(const Directory& parentDirectory)
      {
        std::unique_ptr<T> scriptableObject = ScriptableObject::create<T>("");
        generateScriptableObjectBindings(parentDirectory, Reflection::Type<T>(), *scriptableObject);
      }

      template <typename T>
      static void generateComponentBindings(const Directory& parentDirectory)
      {
        generateComponentBindings(parentDirectory, Reflection::Type<T>());
      }

    private:
      static std::string createDefaultNamespaces();
      static std::string createClassDeclaration(const Reflection::ITypeInfo& typeInfo);
      static std::string createFilePostamble();
  };
}

#endif