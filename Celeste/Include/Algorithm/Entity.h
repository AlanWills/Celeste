#pragma once

#include "Memory/Iterators/ResizeableAllocatorIterator.h"
#include "Memory/Allocators/ResizeableAllocator.h"


namespace Celeste::Algorithm
{
  template <typename T>
  inline void update(ResizeableAllocator<T>& allocator)
  {
    for (T& obj : allocator)
    {
      obj.update();
    }
  }

  template <typename T>
  inline void update(ResizeableAllocator<T>& allocator, float elapsedGameTime)
  {
    for (T& obj : allocator)
    {
      obj.update(elapsedGameTime);
    }
  }
}