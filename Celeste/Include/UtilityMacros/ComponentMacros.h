#pragma once

#include "Templates/ComponentTypeTraits.h"
#include "UtilityMacros/CustomMemoryMacros.h"

  //------------------------------------------------------------------------------------------------
#define COMPONENT_MEMBER_DECLARATION(ComponentType, DllExport) \
  public: \
    DllExport ComponentType(Celeste::GameObject& gameObject); \
    \
  private: \
    static bool m_registered;

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
  bool ComponentType::m_registered = Celeste::ComponentRegistry::registerComponent(ComponentType::type_name(), [](Celeste::GameObject& gameObject) { return gameObject.addComponent<ComponentType>(); });

//------------------------------------------------------------------------------------------------
#define REGISTER_COMPONENT(ComponentType, PoolSize) \
  CUSTOM_MEMORY_CREATION(ComponentType, PoolSize) \
  ADD_COMPONENT_TO_REGISTRY(ComponentType)
