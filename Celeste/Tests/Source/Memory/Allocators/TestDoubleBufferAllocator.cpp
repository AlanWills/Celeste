#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Memory/Allocators/DoubleBufferAllocator.h"

#include <vector>

using namespace Celeste;


namespace TestCeleste
{
  /*
    In this class we use ints specifically and do not test other types
    Should the need arise, extra types may need to be tested, but functionally I currently believe these tests provide enough coverage
  */
  CELESTE_TEST_CLASS(TestDoubleBufferAllocator)

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DoubleBufferAllocator_Constructor_NoErrors)
    {
      DoubleBufferAllocator<char, 1> charAllocator;
      DoubleBufferAllocator<int, 1024> intAllocator;
      DoubleBufferAllocator<void*, 1024> pointerAllocator;
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DoubleBufferAllocator_CanAllocate_ShouldReturnTrue)
    {
      DoubleBufferAllocator<void*, 1024> allocator;
      std::vector<size_t> validAllocs = { 1, 10, 1024 };

      for (size_t validSize : validAllocs)
      {
        Assert::IsTrue(allocator.canAllocate(validSize));
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DoubleBufferAllocator_CanAllocate_ShouldReturnFalse)
    {
      DoubleBufferAllocator<void*, 1024> allocator;
      std::vector<size_t> invalidAllocs = { 1025, 0, INT_MAX };

      for (size_t invalidSize : invalidAllocs)
      {
        Assert::IsFalse(allocator.canAllocate(invalidSize));
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DoubleBufferAllocator_Copy_PassingNullptr_ReturnsInvalidAllocate)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;
      int* buffer = nullptr;

      Assert::IsTrue(intAllocator.copy(5, buffer) == AllocateResult::kInvalidAllocate);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DoubleBufferAllocator_Copy_AllocatingSizeLargerThanBufferSize_ReturnsInvalidAllocate)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;
      int* buffer = nullptr;

      Assert::IsTrue(intAllocator.copy(1025, buffer) == AllocateResult::kInvalidAllocate);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DoubleBufferAllocator_Copy_NoSwapping)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;
      std::vector<int> data = { 0, 5, 10, 15, 20 };

      Assert::AreEqual(AllocateResult::kNoSwapRequired, intAllocator.copy(data.size(), &data.front()));
      intAllocator.swapBuffers();

      const int* bufferStart = nullptr;
      size_t bufferUsage = intAllocator.getBufferedData(&bufferStart);

      // Check we have used the amount of space in the back buffer as our data array
      Assert::AreEqual(data.size(), bufferUsage);

      for (int i = 0; i < data.size(); ++i)
      {
        Assert::AreEqual(data[i], bufferStart[i]);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DoubleBufferAllocator_Copy_Swapping)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;
      std::vector<int> offsetData(1023);
      std::vector<int> data = { 0, 5, 10, 15, 20 };

      // Fake allocate the first 1023 elements (even though we are not filling them out)
      Assert::AreEqual(AllocateResult::kNoSwapRequired, intAllocator.copy(offsetData.size(), &offsetData.front()));
      Assert::AreEqual(AllocateResult::kSwapRequired, intAllocator.copy(data.size(), &data.front()));
      intAllocator.swapBuffers();

      const int* bufferStart = nullptr;
      size_t bufferUsage = intAllocator.getBufferedData(&bufferStart);

      // Check we have used the amount of space in the back buffer as our data array
      Assert::AreEqual(data.size(), bufferUsage);

      for (int i = 0; i < data.size(); ++i)
      {
        // Buffered data should have been completely written to the start of the back buffer
        Assert::AreEqual(data[i], bufferStart[i]);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DoubleBufferAllocator_Copy_Offsetted_NoSwapping)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;
      std::vector<int> offsetData = { 0, 0, 0, 0, 0 };
      std::vector<int> data = { 0, 5, 10, 15, 20 };

      // Fake allocate the first five elements (even though we are not filling them out)
      // Check the allocate result to ensure the validity of our test (if it has swapped then obviously this test is broken!)
      Assert::AreEqual(AllocateResult::kNoSwapRequired, intAllocator.copy(offsetData.size(), &offsetData.front()));
      Assert::AreEqual(AllocateResult::kNoSwapRequired, intAllocator.copy(data.size(), &data.front()));
      intAllocator.swapBuffers();

      const int* bufferStart = nullptr;
      size_t bufferUsage = intAllocator.getBufferedData(&bufferStart);

      // Check we have used the amount of space in the back buffer as our data array and offset data array
      Assert::AreEqual(data.size() + offsetData.size(), bufferUsage);

      for (int i = 0; i < data.size(); ++i)
      {
        Assert::AreEqual(data[i], bufferStart[offsetData.size() + i]);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DoubleBufferAllocator_Allocate_PassingNullptr_ReturnsInvalidAllocate)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;
      int** buffer = nullptr;

      Assert::IsTrue(intAllocator.allocate(5, buffer) == AllocateResult::kInvalidAllocate);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DoubleBufferAllocator_Allocate_AllocatingSizeLargerThanBufferSize_ReturnsInvalidAllocate)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;
      int* buffer = nullptr;

      Assert::IsTrue(intAllocator.allocate(1025, &buffer) == AllocateResult::kInvalidAllocate);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DoubleBufferAllocator_Allocate_NoSwapping)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;
      int* data = nullptr;
      Assert::AreEqual(AllocateResult::kNoSwapRequired, intAllocator.allocate(5, &data));

      for (int i = 0; i < 5; ++i)
      {
        data[i] = i * 5;
      }

      intAllocator.swapBuffers();

      const int* bufferStart = nullptr;
      size_t bufferUsage = intAllocator.getBufferedData(&bufferStart);

      // Check we have used the amount of space in the back buffer as our data array
      Assert::AreEqual((size_t)5, bufferUsage);

      for (int i = 0; i < 5; ++i)
      {
        Assert::AreEqual(i * 5, bufferStart[i]);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DoubleBufferAllocator_Allocate_Swapping)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;
      int* data = nullptr;

      // Fake allocate the first 1023 elements (even though we are not filling them out)
      // Check the allocate result to ensure the validity of our test (if it has swapped then obviously this test is broken!)
      Assert::AreEqual(AllocateResult::kNoSwapRequired, intAllocator.allocate(1023, &data));
      Assert::AreEqual(AllocateResult::kSwapRequired, intAllocator.allocate(5, &data));

      for (int i = 0; i < 5; ++i)
      {
        data[i] = i * 5;
      }

      intAllocator.swapBuffers();

      const int* bufferStart = nullptr;
      size_t bufferUsage = intAllocator.getBufferedData(&bufferStart);

      // Check we have used the amount of space in the back buffer as our data array
      Assert::AreEqual((size_t)5, bufferUsage);

      for (int i = 0; i < 5; ++i)
      {
        // Buffered data should have been completely written to the start of the back buffer
        Assert::AreEqual(i * 5, bufferStart[i]);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DoubleBufferAllocator_Allocate_Offsetted_NoSwapping)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;
      int offset = 5;

      // Fake allocate the first five elements (even though we are not filling them out)
      int* data = nullptr;
      intAllocator.allocate(offset, &data);
      Assert::AreEqual(AllocateResult::kNoSwapRequired, intAllocator.allocate(5, &data));

      for (int i = 0; i < 5; ++i)
      {
        data[i] = i * 5;
      }

      intAllocator.swapBuffers();

      const int* bufferStart = nullptr;
      size_t bufferUsage = intAllocator.getBufferedData(&bufferStart);

      // Check we have used the amount of space in the back buffer as our data array and offset
      Assert::AreEqual((size_t)10, bufferUsage);

      for (int i = 0; i < 5; ++i)
      {
        Assert::AreEqual(i * 5, bufferStart[offset + i]);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DoubleBufferAllocator_DeallocateAllWithEmptyBuffers)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;

      // Initially check the buffers are empty
      const int* bufferStart = nullptr;
      Assert::AreEqual((size_t)0, intAllocator.getBufferedData(&bufferStart));

      intAllocator.swapBuffers();
      Assert::AreEqual((size_t)0, intAllocator.getBufferedData(&bufferStart));

      // Now deallocateAll and check again
      intAllocator.deallocateAll();
      Assert::AreEqual((size_t)0, intAllocator.getBufferedData(&bufferStart));

      intAllocator.swapBuffers();
      Assert::AreEqual((size_t)0, intAllocator.getBufferedData(&bufferStart));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DoubleBufferAllocator_DeallocateAllWithNonEmptyBuffers)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;

      // Allocate in two chunks because we cannot allocate a chunk larger than the buffer size
      int* output = nullptr;
      Assert::AreEqual(AllocateResult::kNoSwapRequired, intAllocator.allocate(500, &output));
      Assert::AreEqual(AllocateResult::kSwapRequired, intAllocator.allocate(800, &output));

      // Initially check the buffers are non-empty
      const int* bufferStart = nullptr;
      Assert::AreNotEqual((size_t)0, intAllocator.getBufferedData(&bufferStart));

      intAllocator.swapBuffers();
      Assert::AreNotEqual((size_t)0, intAllocator.getBufferedData(&bufferStart));

      // Now deallocateAll and check again
      intAllocator.deallocateAll();
      Assert::AreEqual((size_t)0, intAllocator.getBufferedData(&bufferStart));

      intAllocator.swapBuffers();
      Assert::AreEqual((size_t)0, intAllocator.getBufferedData(&bufferStart));
    }
  };
}

//----------------------------------------------------------------------------------------------------------
// Implementation of ToString for allocate result so that we can use Assert::AreEqual on AllocateResult enum
namespace Microsoft::VisualStudio::CppUnitTestFramework {
  template<>
  std::wstring ToString<AllocateResult>(const AllocateResult& coord)
  {
    switch (coord)
    {
    case AllocateResult::kSwapRequired:
      return L"SwapRequired";

    case AllocateResult::kNoSwapRequired:
      return L"NoSwapRequired";

    default:
      return L"";
    }
  }
}