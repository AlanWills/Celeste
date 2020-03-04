#pragma once

#include "Memory/Iterators/EntityAllocatorIterator.h"
#include "Memory/Allocators/PoolAllocator.h"
#include "Memory/ObserverPtr.h"
#include "Debug/Assert.h"
#include "Debug/Log.h"

#include <algorithm>
#include <numeric>
#include <list>
#include <functional>


namespace Celeste
{
  template <typename T>
  class EntityAllocator
  {
    public:
      EntityAllocator(size_t initialCapacity);
      EntityAllocator(EntityAllocator<T>&&) = default;
      EntityAllocator(const EntityAllocator<T>&) = delete;
      ~EntityAllocator() = default;

      EntityAllocator<T>& operator=(const EntityAllocator<T>&) = delete;
      EntityAllocator<T>& operator=(EntityAllocator<T>&&) = default;

      /// Allocates and returns a handle using the templated allocator.
      /// The component will have had initialize already called on it.
      template <typename ...Args>
      observer_ptr<T> allocate(Args&&... args);

      /// Free the memory reserved in the templated allocator for reuse.
      /// die will be called on the object if it hasn't already.
      bool deallocate(T& item);
      void deallocateAll();

      inline EntityAllocatorIterator<T> begin()
      {
        return EntityAllocatorIterator<T>(m_allocators.begin(), m_allocators.end());
      }

      inline EntityAllocatorIterator<const T> begin() const { return cbegin(); }

      inline EntityAllocatorIterator<const T> cbegin() const 
      { 
        return EntityAllocatorIterator<const T>(m_allocators.cbegin(), m_allocators.cend());
      }

      inline EntityAllocatorIterator<T> end()
      { 
        return EntityAllocatorIterator<T>(m_allocators.begin(), m_allocators.back()->end());
      }

      inline EntityAllocatorIterator<const T> end() const { return cend(); }

      inline EntityAllocatorIterator<const T> cend() const 
      {
        return EntityAllocatorIterator<const T>(m_allocators.begin(), static_cast<const PoolAllocator<T>*>(m_allocators.back().get())->end());
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
        return const_cast<EntityAllocator<T>*>(this)->find(predicate);
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

      void handleInput();
      void update(float elapsedGameTime);

    private:
      observer_ptr<PoolAllocator<T>> getAllocator(T& item);

      std::list<std::unique_ptr<PoolAllocator<T>>> m_allocators;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  EntityAllocator<T>::EntityAllocator(size_t initialCapacity) :
    m_allocators()
  {
    m_allocators.emplace_back(std::make_unique<typename Celeste::PoolAllocator<T>>(initialCapacity));
    STATIC_ASSERT((std::is_base_of<Entity, T>::value), "Inputted type is not derived from Entity");
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  template <typename ...Args>
  observer_ptr<T> EntityAllocator<T>::allocate(Args&&... args)
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

    return chosenAllocator->allocate(std::forward<Args>(args)...);
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  bool EntityAllocator<T>::deallocate(T& item)
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
  observer_ptr<typename Celeste::PoolAllocator<T>> EntityAllocator<T>::getAllocator(T& item)
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
  void EntityAllocator<T>::handleInput()
  {
    for (T& object : *this)
    {
      if (object.isActive())
      {
        object.handleInput();
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void EntityAllocator<T>::update(float elapsedGameTime)
  {
    for (T& object : *this)
    {
      if (object.isActive())
      {
        object.update(elapsedGameTime);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void EntityAllocator<T>::deallocateAll()
  {
    for (const auto& allocator : m_allocators)
    {
      allocator->deallocateAll();
    }
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  bool EntityAllocator<T>::contains(const T& object) const
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
  bool EntityAllocator<T>::isAllocated(const T& object) const
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