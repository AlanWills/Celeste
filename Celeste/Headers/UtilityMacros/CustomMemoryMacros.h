#pragma once

#include "Memory/Allocators/EntityAllocator.h"

//------------------------------------------------------------------------------------------------
#define CUSTOM_MEMORY_DECLARATION(Type, DllExport) \
  public: \
    static constexpr const char* const type_name() { return #Type; } \
    \
    void* operator new(size_t); \
    void operator delete(void*); \
    \
  private: \
    using Allocator = Celeste::EntityAllocator<Type>; \
    static Allocator m_allocator;

  //------------------------------------------------------------------------------------------------
#define CUSTOM_MEMORY_CREATION(Type, PoolSize) \
  Type::Allocator Type::m_allocator = Type::Allocator(PoolSize); \
  \
  void* Type::operator new(size_t) \
  { \
    return m_allocator.allocate(); \
  } \
  \
  void Type::operator delete(void* memory) \
  { \
    Type& type = *static_cast<Type*>(memory); \
    ASSERT(m_allocator.isAllocated(type)); \
    \
    if (m_allocator.isAllocated(type)) \
    { \
      m_allocator.deallocate(type); \
    } \
  }