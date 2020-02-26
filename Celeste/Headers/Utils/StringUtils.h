#pragma once

#include "CelesteDllExport.h"

#include <algorithm> 
#include <cctype>
#include <locale>
#include <string>
#include <vector>

namespace Celeste
{
  /// Convert a long string to a normal string and returns the number of characters in the converted string
  CelesteDllExport size_t wcharToChar(const wchar_t* input, char* output, size_t sizeOfOutputBuffer);

  /// Convert a string to a long string and returns the number of characters in the converted string
  CelesteDllExport size_t charToWchar(const char* input, wchar_t* output, size_t sizeOfOutputBuffer);

  /// Split the inputted text into constituent lines by searching for instances of the '\n' character
  CelesteDllExport void getLines(const std::string& text, std::vector<std::string>& outputLines);

  /// Calls to_string on the input and appends it onto the outputStr
  /// Should only be used on primitive numeric types
  /// Cannot control formatting of string so there may be trailing zeroes
  template <typename T>
  inline void numericToStringAppend(T input, std::string& outputStr)
  {
    outputStr.append(std::to_string(input));
  }

  // trim from start (in place)
  inline void ltrim(std::string &s)
  {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) { return !std::isspace(ch); }));
  }

  // trim from end (in place)
  inline void rtrim(std::string &s)
  {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) { return !std::isspace(ch); }).base(), s.end());
  }

  // trim from both ends (in place)
  inline void trim(std::string &s)
  {
    ltrim(s);
    rtrim(s);
  }

  // trim from start (copying)
  inline std::string ltrim_copy(std::string s)
  {
    ltrim(s);
    return s;
  }

  // trim from end (copying)
  inline std::string rtrim_copy(std::string s)
  {
    rtrim(s);
    return s;
  }

  // trim from both ends (copying)
  inline std::string trim_copy(std::string s)
  {
    trim(s);
    return s;
  }

  CelesteDllExport void replaceAll(std::string& original, const std::string& substringToFind, const std::string& substringToReplace);
}