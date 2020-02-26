#pragma once

//------------------------------------------------------------------------------------------------
#define COMPONENT_MEMORY(ComponentType) \
  private: \
    using Alloc = Celeste::EntityAllocator<ComponentType>; \
    static Alloc m_componentAllocator;

  //------------------------------------------------------------------------------------------------
#define COMPONENT_MEMBER_DECLARATION(ComponentType, DllExport) \
  public: \
    static constexpr const char* const type_name() { return #ComponentType; } \
    \
    DllExport ComponentType(); \
    DllExport static ComponentType* allocate(Celeste::GameObject& gameObject); \
    DllExport static bool deallocate(ComponentType& component); \
    DllExport bool deallocate() override; \
    \
  private: \
    static bool m_registered; \
    static bool m_bindingsRegistered;

  //------------------------------------------------------------------------------------------------
#define DECLARE_COMPONENT(ComponentType, Manager, DllExport) \
    private: \
      COMPONENT_MEMORY(ComponentType) \
      COMPONENT_MEMBER_DECLARATION(ComponentType, DllExport); \
    \
    private: \
      friend class Manager;

  //------------------------------------------------------------------------------------------------
#define DECLARE_SCRIPT(ComponentType, DllExport) \
    private: \
      COMPONENT_MEMORY(ComponentType) \
      COMPONENT_MEMBER_DECLARATION(ComponentType, DllExport)

  //------------------------------------------------------------------------------------------------
#define COMPONENT_MEMORY_CREATION(ComponentType, PoolSize) \
    ComponentType::Alloc ComponentType::m_componentAllocator = ComponentType::Alloc(PoolSize);

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
#define COMPONENT_MEMBER_DEFINITION(ComponentType) \
    ComponentType* ComponentType::allocate(Celeste::GameObject& gameObject) \
    { \
      ComponentType* component = m_componentAllocator.allocate(); \
      ASSERT(component->getGameObject() == nullptr); \
      component->setGameObject(gameObject); \
      return component; \
    } \
    \
    bool ComponentType::deallocate(ComponentType& component) \
    { \
      if (m_componentAllocator.isAllocated(component)) \
      { \
        return component.deallocate(); \
      } \
      \
      ASSERT_FAIL(); \
      return false; \
    } \
    \
    bool ComponentType::deallocate() { return m_componentAllocator.deallocate(*this); }

  //------------------------------------------------------------------------------------------------
#define REGISTER_COMPONENT(ComponentType, PoolSize) \
    COMPONENT_MEMORY_CREATION(ComponentType, PoolSize) \
    ADD_COMPONENT_TO_REGISTRY(ComponentType) \
    BINDINGS_GENERATION(ComponentType) \
    COMPONENT_MEMBER_DEFINITION(ComponentType)

  //------------------------------------------------------------------------------------------------
#define REGISTER_SCRIPT(ComponentType, PoolSize) \
    COMPONENT_MEMORY_CREATION(ComponentType, PoolSize) \
    ADD_COMPONENT_TO_REGISTRY(ComponentType) \
    BINDINGS_GENERATION(ComponentType) \
    COMPONENT_MEMBER_DEFINITION(ComponentType)
