#pragma once

#include "Memory/Iterators/ResizeableAllocatorIterator.h"
#include "Memory/Allocators/ResizeableAllocator.h"


namespace Celeste::Algorithm
{
  template <typename T>
  inline void update(float elapsedGameTime, ResizeableAllocator<T>& allocator)
  {
    for (T& obj : allocator)
    {
      obj.update(elapsedGameTime);
    }
  }
}