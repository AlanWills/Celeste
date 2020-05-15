#include "Utils/StringUtils.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  void split(const std::string& text, std::vector<std::string>& outputWords, char delimiter)
  {
    if (text.empty())
    {
      return;
    }

    std::string current;
    current.reserve(text.size());

    for (char c : text)
    {
      if (c == delimiter)
      {
        outputWords.push_back(current);
        current.clear();
      }
      else
      {
        current.push_back(c);
      }
    }

    outputWords.push_back(current);
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