#pragma once

#include "Templates/ComponentTypeTraits.h"
#include "UtilityMacros/CustomMemoryMacros.h"

  //------------------------------------------------------------------------------------------------
#define COMPONENT_MEMBER_DECLARATION(ComponentType, DllExport) \
  public: \
    DllExport ComponentType(Celeste::GameObject& gameObject); \
    \
  private: \
    static bool m_registered; \
    static bool m_bindingsRegistered;

  //------------------------------------------------------------------------------------------------
#define DECLARE_MANAGED_COMPONENT(ComponentType, Manager, DllExport) \
  public: \
    static constexpr bool isManaged() { return true; } \
    \
  private: \
    CUSTOM_MEMORY_DECLARATION(ComponentType, DllExport) \
    COMPONENT_MEMBER_DECLARATION(ComponentType, DllExport); \
    \
    friend class Manager;

  //------------------------------------------------------------------------------------------------
#define DECLARE_UNMANAGED_COMPONENT(ComponentType, DllExport) \
  public: \
    static constexpr bool isManaged() { return false; } \
    \
  private: \
    CUSTOM_MEMORY_DECLARATION(ComponentType, DllExport) \
    COMPONENT_MEMBER_DECLARATION(ComponentType, DllExport)

  //------------------------------------------------------------------------------------------------
#define ADD_COMPONENT_TO_REGISTRY(ComponentType) \
  bool ComponentType::m_registered = ComponentRegistry::registerComponent(ComponentType::type_name(), std::unique_ptr<RegistryAllocator>(new DefaultRegistryAllocator<ComponentType>()));

  //------------------------------------------------------------------------------------------------
#if _DEBUG
#define BINDINGS_GENERATION(ComponentType) \
  bool ComponentType::m_bindingsRegistered = ComponentRegistry::addBindings<ComponentType>();
#else
#define BINDINGS_GENERATION(ComponentType) \
  bool ComponentType::m_bindingsRegistered = false;
#endif

//------------------------------------------------------------------------------------------------
#define REGISTER_MANAGED_COMPONENT(ComponentType, PoolSize) \
  CUSTOM_MEMORY_CREATION(ComponentType, PoolSize) \
  ADD_COMPONENT_TO_REGISTRY(ComponentType) \
  BINDINGS_GENERATION(ComponentType)

//------------------------------------------------------------------------------------------------
#define REGISTER_UNMANAGED_COMPONENT(ComponentType, PoolSize) \
  CUSTOM_MEMORY_CREATION(ComponentType, PoolSize) \
  ADD_COMPONENT_TO_REGISTRY(ComponentType) \
  BINDINGS_GENERATION(ComponentType)
