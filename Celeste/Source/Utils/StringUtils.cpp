#include "Utils/StringUtils.h"
#include <stdlib.h>


namespace Celeste
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

  //------------------------------------------------------------------------------------------------
  void getLines(const std::string& text, std::vector<std::string>& outputLines)
  {
    if (text.empty())
    {
      return;
    }

    std::string currentSubLine;
    currentSubLine.reserve(text.size());

    for (char c : text)
    {
      if (c == '\n')
      {
        outputLines.push_back(currentSubLine);
        currentSubLine.clear();
      }
      else
      {
        currentSubLine.push_back(c);
      }
    }

    outputLines.push_back(currentSubLine);
  }

  //------------------------------------------------------------------------------------------------
  void replaceAll(std::string& original, const std::string& substringToFind, const std::string& substringToReplace)
  {
    if (!substringToFind.empty())
    {
      size_t start_pos = 0;
      while ((start_pos = original.find(substringToFind, start_pos)) != std::string::npos)
      {
        original.replace(start_pos, substringToFind.length(), substringToReplace);
        start_pos += substringToReplace.length();
      }
    }
  }
}