#pragma once

#include "CelesteDllExport.h"


namespace Celeste
{

class CelesteDllExport AlignedAllocator
{
  public:
    AlignedAllocator();
    ~AlignedAllocator();

    // Have templated version too?
    void* allocateUnaligned(size_t numberOfBytes) const;

    /// \brief Alignment must be a power of 2
    void* allocateAligned(size_t numberOfBytes, size_t alignment) const;
};

};