#include "Memory/Allocators/AlignedAllocator.h"

#include <assert.h>
#include <memory>


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  AlignedAllocator::AlignedAllocator()
  {
  }

  //------------------------------------------------------------------------------------------------
  AlignedAllocator::~AlignedAllocator()
  {
  }

  //------------------------------------------------------------------------------------------------
  void* AlignedAllocator::allocateUnaligned(size_t numberOfBytes) const
  {
    return malloc(numberOfBytes);
  }

  //------------------------------------------------------------------------------------------------
  void* AlignedAllocator::allocateAligned(size_t numberOfBytes, size_t alignment) const
  {
    // Clients must call allocateUnaligned and freeAligned if alignment is 1
    assert(alignment > 1);

    // Work out the total number of bytes to allocate
    size_t expandedSize = numberOfBytes + alignment;

    // Allocate an unaligned block using this expanded size and then
    // return the raw value of the address
    size_t rawAddress = (size_t)allocateUnaligned(expandedSize);

    // Calculate adjustment by working out how far our last digit is away from a multiple of alignment
    // Rounding up using a mask
    size_t mask = (alignment - 1);
    size_t misalignment = (rawAddress & mask);
    size_t adjustment = alignment - misalignment;

    // Calculate the adjusted aligned address and return as a pointer
    size_t alignedAddress = rawAddress + adjustment;

    // Store the adjustment in the four bytes immediately
    // preceding the adjusted address that we’re returning.
    size_t* pAdjustment = (size_t*)(alignedAddress - sizeof(size_t));
    *pAdjustment = adjustment;

    return (void*)alignedAddress;
  }
}