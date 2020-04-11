#pragma once

#include "Memory/Iterators/ResizeableAllocatorIterator.h"
#include "Memory/Allocators/PoolAllocator.h"
#include "Memory/ObserverPtr.h"
#include "Assert/Assert.h"
#include "Log/Log.h"

#include <algorithm>
#include <numeric>
#include <list>
#include <functional>


namespace Celeste
{
  template <typename T>
  class ResizeableAllocator
  {
    public:
      ResizeableAllocator(size_t initialCapacity);
      ResizeableAllocator(ResizeableAllocator<T>&&) = default;
      ResizeableAllocator(const ResizeableAllocator<T>&) = delete;
      ~ResizeableAllocator() = default;

      ResizeableAllocator<T>& operator=(const ResizeableAllocator<T>&) = delete;
      ResizeableAllocator<T>& operator=(ResizeableAllocator<T>&&) = default;

      observer_ptr<T> allocate();
      
      bool deallocate(T& item);
      void deallocateAll();

      inline ResizeableAllocatorIterator<T> begin()
      {
        return ResizeableAllocatorIterator<T>(m_allocators.begin(), m_allocators.end());
      }

      inline ResizeableAllocatorIterator<const T> begin() const { return cbegin(); }

      inline ResizeableAllocatorIterator<const T> cbegin() const 
      { 
        return ResizeableAllocatorIterator<const T>(m_allocators.cbegin(), m_allocators.cend());
      }

      inline ResizeableAllocatorIterator<T> end()
      { 
        return ResizeableAllocatorIterator<T>(m_allocators.begin(), m_allocators.back()->end());
      }

      inline ResizeableAllocatorIterator<const T> end() const { return cend(); }

      inline ResizeableAllocatorIterator<const T> cend() const 
      {
        return ResizeableAllocatorIterator<const T>(m_allocators.begin(), static_cast<const PoolAllocator<T>*>(m_allocators.back().get())->end());
      }

      bool contains(const T& entity) const;
      bool isAllocated(const T& entity) const;

      observer_ptr<T> find(const std::function<bool(const T&)>& predicate)
      {
        auto it = begin();
        auto endIt = end();

        while (it != endIt)
        {
          if (predicate(*it))
          {
            return &*it;
          }
          
          ++it;
        }

        return nullptr;
      }

      observer_ptr<const T> find(const std::function<bool(const T&)>& predicate) const
      {
        return const_cast<ResizeableAllocator<T>*>(this)->find(predicate);
      }

      void findAll(const std::function<bool(const T&)>& predicate, std::vector<std::reference_wrapper<T>>& foundObjects)
      {
        auto it = begin();
        auto endIt = end();

        while (it != endIt)
        {
          if (predicate(*it))
          {
            foundObjects.push_back(*it);
          }

          ++it;
        }
      }

      void findAll(const std::function<bool(const T&)>& predicate, std::vector<std::reference_wrapper<const T>>& foundObjects) const
      {
        auto it = cbegin();
        auto endIt = cend();

        while (it != endIt)
        {
          if (predicate(*it))
          {
            foundObjects.push_back(*it);
          }

          ++it;
        }
      }

      size_t size() const 
      { 
        return std::accumulate(m_allocators.begin(), m_allocators.end(), static_cast<size_t>(0),
          [](size_t total, const std::unique_ptr<PoolAllocator<T>>& allocator)
          {
            return total + allocator->size();
          });
      }

    private:
      observer_ptr<PoolAllocator<T>> getAllocator(T& item);

      std::list<std::unique_ptr<PoolAllocator<T>>> m_allocators;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  ResizeableAllocator<T>::ResizeableAllocator(size_t initialCapacity) :
    m_allocators()
  {
    m_allocators.emplace_back(std::make_unique<typename Celeste::PoolAllocator<T>>(initialCapacity));
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  observer_ptr<T> ResizeableAllocator<T>::allocate()
  {
    // Find an allocator with space
    observer_ptr<typename Celeste::PoolAllocator<T>> chosenAllocator = nullptr;
    auto allocWithSpace = std::find_if(m_allocators.begin(), m_allocators.end(),
      [](const auto& allocator)
      {
        return allocator->canAllocate(1);
      });

    if (allocWithSpace == m_allocators.end())
    {
      m_allocators.emplace_back(std::make_unique<typename Celeste::PoolAllocator<T>>(m_allocators.front()->capacity()));
      chosenAllocator = m_allocators.back().get();
    }
    else
    {
      chosenAllocator = (*allocWithSpace).get();
    }

    return chosenAllocator->allocate();
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  bool ResizeableAllocator<T>::deallocate(T& item)
  {
    observer_ptr<typename Celeste::PoolAllocator<T>> allocator = getAllocator(item);
    if (allocator == nullptr)
    {
      ASSERT_FAIL();
      return false;
    }

    // Deallocate the actual memory
    return allocator->deallocate(item);
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  observer_ptr<typename Celeste::PoolAllocator<T>> ResizeableAllocator<T>::getAllocator(T& item)
  {
    for (const auto& allocator : m_allocators)
    {
      if (allocator->contains(item))
      {
        return allocator.get();
      }
    }

    ASSERT_FAIL();
    return nullptr;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void ResizeableAllocator<T>::deallocateAll()
  {
    for (const auto& allocator : m_allocators)
    {
      allocator->deallocateAll();
    }
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  bool ResizeableAllocator<T>::contains(const T& object) const
  {
    for (const auto& allocator : m_allocators)
    {
      if (allocator->contains(object))
      {
        return true;
      }
    }

    return false;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  bool ResizeableAllocator<T>::isAllocated(const T& object) const
  {
    for (const auto& allocator : m_allocators)
    {
      if (allocator->isAllocated(object))
      {
        return true;
      }
    }

    return false;
  }
}