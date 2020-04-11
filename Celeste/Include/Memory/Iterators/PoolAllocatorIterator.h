#pragma once

#include <iterator>


namespace Celeste
{
  template <typename T>
  class PoolAllocatorIterator
  {
    public:
      using iterator_category = std::forward_iterator_tag;
      using value_type = T;
      using difference_type = ptrdiff_t;
      using pointer = T*;
      using reference = T&;

      PoolAllocatorIterator(T* ptr);
      PoolAllocatorIterator(T* ptr, const bool* allocated, size_t size);
      PoolAllocatorIterator(const PoolAllocatorIterator<T>&);
      
      PoolAllocatorIterator<T>& operator=(const PoolAllocatorIterator<T>&);

      inline PoolAllocatorIterator<T>& operator++();
      inline PoolAllocatorIterator<T> operator++(int);

      inline bool operator==(const PoolAllocatorIterator<T>& other) const { return m_ptr == other.get(); }
      inline bool operator!=(const PoolAllocatorIterator<T>& other) const { return !(*this == other); }

      inline T& operator*() const { return *m_ptr; }
      inline T* get() const { return m_ptr; }

    private:
      inline void next() 
      { 
        ++m_ptr;
        ++m_current;
      }

      inline void advance()
      {
        while (m_current < m_size && !m_allocated[m_current])
        {
          next();
        }
      }

      T* m_ptr;
      const bool* m_allocated;
      size_t m_size;
      size_t m_current = 0;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  PoolAllocatorIterator<T>::PoolAllocatorIterator(T* ptr) :
    m_ptr(ptr),
    m_allocated(nullptr),
    m_size(0),
    m_current(0)
  {
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  PoolAllocatorIterator<T>::PoolAllocatorIterator(T* ptr, const bool* allocated, size_t size) :
    m_ptr(ptr),
    m_allocated(allocated),
    m_size(size),
    m_current(0)
  {
    advance();
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  PoolAllocatorIterator<T>::PoolAllocatorIterator(const PoolAllocatorIterator<T>& rhs) :
    m_ptr(rhs.m_ptr),
    m_allocated(rhs.m_allocated),
    m_size(rhs.m_size),
    m_current(rhs.m_current)
  {
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  PoolAllocatorIterator<T>& PoolAllocatorIterator<T>::operator=(const PoolAllocatorIterator<T>& rhs)
  {
    m_ptr = rhs.m_ptr;
    m_allocated = rhs.m_allocated;
    m_size = rhs.m_size;
    m_current = rhs.m_current;

    return *this;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  PoolAllocatorIterator<T>& PoolAllocatorIterator<T>::operator++()
  {
    next();
    advance();
    return *this;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  PoolAllocatorIterator<T> PoolAllocatorIterator<T>::operator++(int)
  {
    next();
    advance();
    return PoolAllocatorIterator<T>(*this);
  }
}