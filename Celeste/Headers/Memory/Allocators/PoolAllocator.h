#pragma once

#include "Debug/Assert.h"
#include "Memory/Iterators/PoolAllocatorIterator.h"


namespace Celeste
{
  template <typename T>
  class PoolAllocator
  {
    public:
      using type = T;
      using iterator = PoolAllocatorIterator<T>;
      using const_iterator = PoolAllocator<const T>;

      PoolAllocator(size_t capacity);
      ~PoolAllocator();
      PoolAllocator(PoolAllocator<T>&& rhs);
      PoolAllocator(const PoolAllocator<T>&) = delete;

      PoolAllocator<T>& operator=(PoolAllocator<T>&& rhs);
      PoolAllocator<T>& operator=(const PoolAllocator<T>&) = delete;

      inline bool canAllocate(size_t count) const { return m_capacity - m_size >= count; }

      template <typename ...Args>
      T* allocate(Args&&... args);

      bool deallocate(T& item);
      void deallocateAll();

      inline bool contains(const T& item) const { return static_cast<size_t>(&item - m_pool) < m_capacity; }
      inline bool isAllocated(const T& item) const { return contains(item) && m_allocated[&item - m_pool]; }

      inline PoolAllocatorIterator<T> begin() { return PoolAllocatorIterator<T>(m_pool, m_allocated, m_capacity); }
      inline PoolAllocatorIterator<T> end() { return PoolAllocatorIterator<T>(m_pool + m_capacity); }

      inline PoolAllocatorIterator<const T> begin() const { return PoolAllocatorIterator<const T>(m_pool, m_allocated, m_capacity); }
      inline PoolAllocatorIterator<const T> end() const { return PoolAllocatorIterator<const T>(m_pool + m_capacity); }

      inline size_t size() const { return m_size; }
      inline size_t capacity() const { return m_capacity; }
      
    private:
      using PoolMemory = std::unique_ptr<T[], void(*)(T*)>;
      using AllocatedMemory = std::unique_ptr<bool>;

      PoolMemory m_poolMemory;
      AllocatedMemory m_allocatedMemory;
      T* m_pool;
      bool* m_allocated;

      size_t m_size;
      size_t m_capacity;
      size_t m_hint;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  PoolAllocator<T>::PoolAllocator(size_t capacity) :
    m_poolMemory(
      static_cast<T*>(::operator new(capacity * sizeof(T))),
      [](T* b) {::operator delete[](b); }),
    m_allocatedMemory(new bool[capacity]),
    m_pool(m_poolMemory.get()),
    m_allocated(m_allocatedMemory.get()),
    m_size(0),
    m_capacity(capacity),
    m_hint(0)
  {
    for (size_t i = 0; i < capacity; ++i)
    {
      m_allocated[i] = false;
    }
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  PoolAllocator<T>::PoolAllocator(Celeste::PoolAllocator<T>&& rhs) :
    m_poolMemory(std::move(rhs.m_poolMemory)),
    m_allocatedMemory(std::move(rhs.m_allocatedMemory)),
    m_pool(m_poolMemory.get()),
    m_allocated(m_allocatedMemory.get()),
    m_size(rhs.m_size),
    m_capacity(rhs.m_capacity),
    m_hint(rhs.m_hint)
  {
  }


  //------------------------------------------------------------------------------------------------
  template <typename T>
  PoolAllocator<T>::~PoolAllocator()
  {
    deallocateAll();
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  PoolAllocator<T>& PoolAllocator<T>::operator=(Celeste::PoolAllocator<T>&& rhs)
  {
    m_poolMemory = std::move(rhs.m_poolMemory);
    m_allocatedMemory = std::move(rhs.m_allocatedMemory);
    m_pool = m_poolMemory.get();
    m_allocated = m_allocatedMemory.get();
    m_size = rhs.m_size;
    m_capacity = rhs.m_capacity;
    m_hint = rhs.m_hint;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  template <typename ...Args>
  T* PoolAllocator<T>::allocate(Args&&... args)
  {
#if _DEBUG
    if (!canAllocate(1))
    {
      ASSERT_FAIL();
      return nullptr;
    }
#endif

    size_t allocationIndex = m_hint;
    if (m_allocated[allocationIndex])
    {
      allocationIndex = 0;
      while (allocationIndex < m_capacity && m_allocated[allocationIndex]) 
      {
        ++allocationIndex;
      }
    }

    ++m_size;
    m_allocated[allocationIndex] = true;
    return ::new (m_pool + allocationIndex) T(std::forward<Args>(args)...);
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  bool PoolAllocator<T>::deallocate(T& item)
  {
#if _DEBUG
    if (!contains(item))
    {
      ASSERT_FAIL();
      return false;
    }

    if (!isAllocated(item))
    {
      ASSERT_FAIL();
      return false;
    }
#endif

    size_t poolIndex = &item - m_pool;

    item.~T();
    m_allocated[poolIndex] = false;
    m_size--;
    m_hint = poolIndex;

    return true;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void PoolAllocator<T>::deallocateAll()
  {
    for (size_t i = 0; i < m_capacity; ++i)
    {
      if (m_allocated[i])
      {
        deallocate(m_pool[i]);
      }
    }

    m_size = 0;
    m_hint = 0;
  }
}