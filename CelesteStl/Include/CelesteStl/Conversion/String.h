#pragma once

#include <string>
#include <vector>

namespace celstl
{
  /// Convert a long string to a normal string and returns the number of characters in the converted string
  size_t wcharToChar(const wchar_t* input, char* output, size_t sizeOfOutputBuffer);

  /// Convert a string to a long string and returns the number of characters in the converted string
  size_t charToWchar(const char* input, wchar_t* output, size_t sizeOfOutputBuffer);
}