#pragma once

#include "Memory/Allocators/PoolAllocator.h"
#include "Templates/ChooseClass.h"

#include <list>
#include <iterator>
#include <type_traits>


namespace Celeste
{
  template <typename T>
  class EntityAllocatorIterator : std::iterator<std::forward_iterator_tag, T>
  {
    private:
      using Iterator = typename choose_class<
        std::is_const<T>::value,
        typename std::list<std::unique_ptr<PoolAllocator<typename std::remove_const<T>::type>>>::const_iterator,
        typename std::list<std::unique_ptr<PoolAllocator<T>>>::iterator>::type;
      
      using AllocatorType = typename choose_class<
        std::is_const<T>::value,
        typename const PoolAllocator<typename std::remove_const<T>::type>*,
        typename PoolAllocator<typename std::remove_const<T>::type>*>::type;

    public:
      EntityAllocatorIterator(typename Iterator allocatorEndIt, PoolAllocatorIterator<T> entityEndIt);
      EntityAllocatorIterator(typename Iterator allocatorIt, typename Iterator allocatorEndIt);
      EntityAllocatorIterator(const EntityAllocatorIterator<T>&) = default;
      EntityAllocatorIterator(EntityAllocatorIterator<T>&&) = default;
      
      EntityAllocatorIterator<T>& operator=(const EntityAllocatorIterator<T>&) = default;
      EntityAllocatorIterator<T>& operator=(EntityAllocatorIterator<T>&&) = default;

      EntityAllocatorIterator& operator++();
      EntityAllocatorIterator operator++(int);

      inline bool operator==(const EntityAllocatorIterator<T>& other) const { return m_entityIt.get() == other.get(); }
      inline bool operator!=(const EntityAllocatorIterator<T>& other) const { return !(*this == other); }

      inline T& operator*() const { return *m_entityIt; }
      inline T* get() const { return m_entityIt.get(); }

    private:
      inline void next()
      {
        ++m_entityIt;
      }

      inline void advanceEntity()
      {
        while (m_entityIt != m_entityEndIt && !(*m_entityIt).isAlive())
        {
          next();
        }
      }

      inline void advance()
      {
        advanceEntity();

        while (m_entityIt == m_entityEndIt && ++m_allocatorIt != m_allocatorEndIt)
        {
          // We are at the end of the allocator, but not in an allocated entry
          // We move to the next allocator
          m_entityIt = static_cast<AllocatorType>((*m_allocatorIt).get())->begin();
          m_entityEndIt = static_cast<AllocatorType>((*m_allocatorIt).get())->end();

          advanceEntity();
        }
      }

      typename Iterator m_allocatorIt;
      typename Iterator m_allocatorEndIt;
      PoolAllocatorIterator<T> m_entityIt;
      PoolAllocatorIterator<T> m_entityEndIt;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  EntityAllocatorIterator<T>::EntityAllocatorIterator(
    typename Iterator allocatorIt,
    typename Iterator allocatorEndIt)
    : m_allocatorIt(allocatorIt),
      m_allocatorEndIt(allocatorEndIt),
      m_entityIt(static_cast<AllocatorType>((*m_allocatorIt).get())->begin()),
      m_entityEndIt(static_cast<AllocatorType>((*m_allocatorIt).get())->end())
  {
    STATIC_ASSERT((std::is_base_of<Entity, T>::value), "Inputted type is not derived from Entity");
    advance();
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  EntityAllocatorIterator<T>::EntityAllocatorIterator(
    typename Iterator allocatorEndIt, 
    PoolAllocatorIterator<T> entityEndIt)
    : m_allocatorIt(allocatorEndIt),
      m_allocatorEndIt(allocatorEndIt),
      m_entityIt(entityEndIt),
      m_entityEndIt(entityEndIt)
  {
    STATIC_ASSERT((std::is_base_of<Entity, T>::value), "Inputted type is not derived from Entity");
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  EntityAllocatorIterator<T>& EntityAllocatorIterator<T>::operator++()
  {
    next();
    advance();
    return *this;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  EntityAllocatorIterator<T> EntityAllocatorIterator<T>::operator++(int)
  {
    next();
    advance();
    return EntityAllocatorIterator<T>(*this);
  }
}