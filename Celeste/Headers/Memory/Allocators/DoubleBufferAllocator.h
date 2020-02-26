#pragma once

#include "Debug/Assert.h"


namespace Celeste
{
  /// \brief An enum which can be used when allocating to determine if we had to swap our buffers
  /// This can be used after an allocation to process the buffered data
  enum class AllocateResult
  {
    kSwapRequired,
    kNoSwapRequired,
    kInvalidAllocate,
  };

  // This class allocates two arrays of the inputted type
  // It then fills one until there is not enough room left for new allocations
  // It then swaps to fill the other array whilst the first is cleared
  // The class does not take responsibility for clearing and will overwrite any buffered array if it runs out of memory
  // Therefore, if a filled array is likely to be kept around for a while before being emptied, either make the array sizes large enough
  // to not require an overwrite, or use a different allocator
  template <typename T, size_t BufferSize>
  class DoubleBufferAllocator
  {
    public:
      DoubleBufferAllocator();
      ~DoubleBufferAllocator();

      /// \brief Checks to see whether there is the desired number of slots left in the current buffer
      /// Returns true if the desired amount of space can be successfully allocated with swapping buffers
      bool canAllocate(size_t desiredBufferSpace) const;

      /// \brief Take a pointer to the start of a chunk of inputted data and copy the values into the current in use buffer
      /// Will swap the buffers before copying if required to
      /// Safer than allocate, but less efficient as we are copying values
      AllocateResult copy(size_t space, const T* data);

      /// \brief Retrieve a pointer to the head of the current in use buffer
      /// Will swap the buffers before returning the pointer in case the current buffer does not have enough room
      /// Use when you are about to create an array of T and you know an upper bound for it's size
      /// No copying is required as you are returning the memory to assign your values to so faster than copy
      AllocateResult allocate(size_t desiredSpace, T** outputData);

      /// \brief Flushes both the front and the back buffer and resets the head index.
      void deallocateAll()
      {
        flushCurrentBuffer();
        swapBuffers();
        flushCurrentBuffer();
      }

      /// \brief Changes around the current in use buffer and resets our element index
      void swapBuffers();

      /// \brief Utility function for returning the start of the back buffer and the amount of the back buffer that was used
      size_t getBufferedData(const T** dataStart) const;

    private:
      /// \brief Utility function to swap buffers if we do not have enough to allocate the requested amount
      AllocateResult checkSpaceAndSwapBuffersIfNecessary(size_t requestedSpace);

      void flushCurrentBuffer();

      T m_bufferOne[BufferSize];
      T m_bufferTwo[BufferSize];

      size_t m_index;
      size_t m_backBufferSpaceUsage;
      T* m_currentBuffer;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T, size_t BufferSize>
  DoubleBufferAllocator<T, BufferSize>::DoubleBufferAllocator() :
    m_index(0),
    m_backBufferSpaceUsage(0),
    m_currentBuffer(m_bufferOne),
    m_bufferOne(),
    m_bufferTwo()
  {
  }

  //------------------------------------------------------------------------------------------------
  template <typename T, size_t BufferSize>
  DoubleBufferAllocator<T, BufferSize>::~DoubleBufferAllocator()
  {
  }

  //------------------------------------------------------------------------------------------------
  template <typename T, size_t BufferSize>
  bool DoubleBufferAllocator<T, BufferSize>::canAllocate(size_t desiredBufferSpace) const
  {
    ASSERT_MSG(desiredBufferSpace >= 0, "Must request an allocation of at least 1 slot");
    return (BufferSize - m_index) >= desiredBufferSpace && desiredBufferSpace > 0;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T, size_t BufferSize>
  AllocateResult DoubleBufferAllocator<T, BufferSize>::copy(size_t count, const T* data)
  {
    if (!data || count > BufferSize)
    {
      ASSERT_FAIL();
      return AllocateResult::kInvalidAllocate;
    }

    AllocateResult result = checkSpaceAndSwapBuffersIfNecessary(count);

    for (int i = 0; i < count; i++)
    {
      m_currentBuffer[m_index] = data[i];
      m_index++;
    }

    return result;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T, size_t BufferSize>
  AllocateResult DoubleBufferAllocator<T, BufferSize>::allocate(size_t desiredSpace, T** outputData)
  {
    if (!outputData || desiredSpace > BufferSize)
    {
      ASSERT_FAIL();
      return AllocateResult::kInvalidAllocate;
    }

    AllocateResult result = checkSpaceAndSwapBuffersIfNecessary(desiredSpace);

    *outputData = &m_currentBuffer[m_index];
    m_index += desiredSpace;

    return result;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T, size_t BufferSize>
  size_t DoubleBufferAllocator<T, BufferSize>::getBufferedData(const T** dataStart) const
  {
    *dataStart = m_currentBuffer == m_bufferOne ? m_bufferTwo : m_bufferOne;

    return m_backBufferSpaceUsage;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T, size_t BufferSize>
  AllocateResult DoubleBufferAllocator<T, BufferSize>::checkSpaceAndSwapBuffersIfNecessary(size_t requestedSpace)
  {
    AllocateResult result = AllocateResult::kNoSwapRequired;

    if (!canAllocate(requestedSpace))
    {
      swapBuffers();

      // Our buffers should be large enough now we have swapped to allocate room for the data - otherwise we are screwed
      ASSERT_MSG(canAllocate(requestedSpace), "Requested space is too large for a full buffer");

      result = AllocateResult::kSwapRequired;
    }

    return result;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T, size_t BufferSize>
  void DoubleBufferAllocator<T, BufferSize>::swapBuffers()
  {
    // Swap the current buffer head over and set the head to the start of the new buffer array
    m_currentBuffer = m_currentBuffer == m_bufferOne ? m_bufferTwo : m_bufferOne;

    m_backBufferSpaceUsage = m_index;
    m_index = 0;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T, size_t BufferSize>
  void DoubleBufferAllocator<T, BufferSize>::flushCurrentBuffer()
  {
    for (size_t i = 0; i < BufferSize; ++i)
    {
      m_currentBuffer[i] = 0;
    }
  }
};