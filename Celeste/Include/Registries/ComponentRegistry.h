#pragma once

#include "CelesteDllExport.h"
#include "Reflection/Type.h"
#include "CelesteStl/Memory/ObserverPtr.h"

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
      using ComponentCreationFunction = std::function<observer_ptr<Component>(GameObject&)>;

    private:
      using ComponentMap = std::unordered_map<std::string, ComponentCreationFunction>;

    public:
      ComponentRegistry() = delete;
      ~ComponentRegistry();
      ComponentRegistry(const ComponentRegistry&) = delete;
      ComponentRegistry& operator=(const ComponentRegistry&) = delete;

      template <typename TComponent>
      static bool registerComponent();
      static bool registerComponent(const std::string& name, const ComponentCreationFunction& creationFunction);

      template <typename T>
      static void deregisterComponent() { deregisterComponent(T::type_name()); }
      static void deregisterComponent(const std::string& name);

      template <typename T>
      static bool hasComponent() { return hasComponent(T::type_name()); }
      static bool hasComponent(const std::string& name) { return getComponents().find(name) != getComponents().end(); }

      static observer_ptr<Component> createComponent(const std::string& componentName, GameObject& gameObject);

    private:
      static ComponentMap& getComponents();
  };

  //------------------------------------------------------------------------------------------------
  template <typename TComponent>
  bool ComponentRegistry::registerComponent()
  {
    return registerComponent(TComponent::type_name(), [](GameObject& gameObject) { return gameObject.addComponent<TComponent>(); });
  }
}