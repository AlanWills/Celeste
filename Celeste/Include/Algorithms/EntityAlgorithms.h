#pragma once

#include "Memory/Iterators/ResizeableAllocatorIterator.h"
#include "Memory/Allocators/ResizeableAllocator.h"


namespace Celeste::Algorithms
{
  template <typename T>
  inline void handleInput(ResizeableAllocatorIterator<T> begin, ResizeableAllocatorIterator<T> end)
  {
    while (begin != end)
    {
      (*begin).handleInput();
      ++begin;
    }
  }

  template <typename T>
  inline void handleInput(ResizeableAllocator<T>& allocator)
  {
    handleInput<T>(allocator.begin(), allocator.end());
  }

  template <typename T>
  inline void update(float elapsedGameTime, ResizeableAllocatorIterator<T> begin, ResizeableAllocatorIterator<T> end)
  {
    while (begin != end)
    {
      (*begin).update(elapsedGameTime);
      ++begin;
    }
  }

  template <typename T>
  inline void update(float elapsedGameTime, ResizeableAllocator<T>& allocator)
  {
    update<T>(elapsedGameTime, allocator.begin(), allocator.end());
  }
}