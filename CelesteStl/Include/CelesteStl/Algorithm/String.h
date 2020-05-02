#pragma once

#include <string>
#include <algorithm>


namespace celstl
{
  void replace(std::string& str, char oldCharacter, char newCharacter)
  {
    std::replace(str.begin(), str.end(), oldCharacter, newCharacter);
  }
}