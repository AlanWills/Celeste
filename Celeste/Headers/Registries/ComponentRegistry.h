#pragma once

#include "CelesteDllExport.h"
#include "Reflection/Type.h"
#include "RegistryAllocator.h"
#include "Memory/ObserverPtr.h"

#include <functional>
#include <unordered_map>


namespace Celeste
{
  class GameObject;
  class Component;
  class Directory;
  class Path;

  template <typename T>
  class DefaultRegistryAllocator;

  class CelesteDllExport ComponentRegistry
  {
    public:
      typedef std::function<void(const std::string&, const Path& filePath)> BindingCallback;

    private:
      // Probably don't need to worry about the shared_ptr, but what the hell
      using ComponentMap = std::unordered_map<std::string, std::unique_ptr<RegistryAllocator>>;
      using ComponentBindingStorageValue = std::unique_ptr<Reflection::ITypeInfo>;
      using ComponentBindingStorage = std::vector<ComponentBindingStorageValue>;

    public:
      ComponentRegistry() = delete;
      ~ComponentRegistry();
      ComponentRegistry(const ComponentRegistry&) = delete;
      ComponentRegistry& operator=(const ComponentRegistry&) = delete;

      template <typename TComponent, typename TAllocator = DefaultRegistryAllocator<TComponent>>
      static bool registerComponent();
      static bool registerComponent(const std::string& name, std::unique_ptr<RegistryAllocator>&& allocator);

  #if _DEBUG
      template <typename T>
      static bool addBindings();
  #endif

      template <typename T>
      static void deregisterComponent() { deregisterComponent(T::type_name()); }
      static void deregisterComponent(const std::string& name);

      template <typename T>
      static bool hasComponent() { return hasComponent(T::type_name()); }
      static bool hasComponent(const std::string& name) { return getComponents().find(name) != getComponents().end(); }

      static observer_ptr<Component> allocateComponent(const std::string& componentName, GameObject& gameObject);

  #if _DEBUG
      static void generateAllBindings(const Directory& destinationDirectory, const BindingCallback& onBindingGenerated);
      static void generateAllBindings(const Directory& destinationDirectory)
      {
        generateAllBindings(destinationDirectory, [](const std::string&, const Path&) -> void {});
      }

      static void generateBindingsForAssembly(const std::string& assembly, const Directory& destinationDirectory, const BindingCallback& onBindingGenerated);
      static void generateBindingsForAssembly(const std::string& assembly, const Directory& destinationDirectory)
      {
        generateBindingsForAssembly(assembly, destinationDirectory, [](const std::string&, const Path&) -> void {});
      }
  #endif

    private:
      static ComponentMap& getComponents();

  #if _DEBUG
      static ComponentBindingStorage& getBindings();
  #endif
};

//------------------------------------------------------------------------------------------------
template <typename TComponent, typename TAllocator>
bool ComponentRegistry::registerComponent()
{
  return registerComponent(TComponent::type_name(), std::unique_ptr<RegistryAllocator>(new TAllocator()));
}

#if _DEBUG
//------------------------------------------------------------------------------------------------
template <typename T>
bool ComponentRegistry::addBindings()
{
  getBindings().emplace_back(std::unique_ptr<Reflection::Type<T>>());
  return true;
}
#endif

}