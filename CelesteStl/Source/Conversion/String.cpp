#include "Conversion/String.h"

#include <stdlib.h>


namespace celstl
{
  //------------------------------------------------------------------------------------------------
  size_t wcharToChar(const wchar_t* input, char* output, size_t sizeOfOutputBuffer)
  {
    size_t numConverted = 0;
    wcstombs_s(&numConverted, output, sizeOfOutputBuffer, input, sizeOfOutputBuffer);

    // Don't care about null terminator, so remove it from count of characters converted
    return numConverted - 1;
  }

  //------------------------------------------------------------------------------------------------
  size_t charToWchar(const char* input, wchar_t* output, size_t sizeOfOutputBuffer)
  {
    size_t numConverted = 0;
    mbstowcs_s(&numConverted, output, sizeOfOutputBuffer, input, sizeOfOutputBuffer);

    // Don't care about null terminator, so remove it from count of characters converted
    return numConverted - 1;
  }
}