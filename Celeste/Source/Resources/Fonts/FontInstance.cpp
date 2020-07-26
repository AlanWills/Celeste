#include "Resources/Fonts/FontInstance.h"
#include "Utils/StringUtils.h"


namespace Celeste::Resources
{
  //------------------------------------------------------------------------------------------------
  FontInstance::FontInstance(const Characters& fontCharacters, float height, const Font& font) :
    m_characters(fontCharacters),
    m_height(height),
    m_font(font)
  {
  }

  //------------------------------------------------------------------------------------------------
  const Character* FontInstance::getCharacter(GLchar character) const
  {
    auto it = m_characters.find(character);
    if (it == m_characters.end())
    {
      ASSERT_FAIL();
      return nullptr;
    }

    return &((*it).second);
  }

  //------------------------------------------------------------------------------------------------
  glm::vec2 FontInstance::measureString(std::string::const_iterator start, std::string::const_iterator end) const
  {
    if (start == end)
    {
      return glm::vec2(0, m_height);
    }

    float x = 0, currentX = 0;
    int y = 0;

    while (start != end)
    {
      const Character* character = getCharacter(*start);
      ASSERT_NOT_NULL(character);

      if (character != nullptr)
      {
        if (*start == '\n')
        {
          ++y;
          x = (std::max)(x, currentX);
          currentX = 0;
        }
        else
        {
          currentX += character->m_advance;
        }
      }

      ++start;
    }

    ++y;
    x = (std::max)(x, currentX);
    currentX = 0;

    return glm::vec2(x, y * m_height);
  }

  //------------------------------------------------------------------------------------------------
  glm::vec2 FontInstance::measureString(const std::string& text) const
  {
    return measureString(text.begin(), text.end());
  }

  //------------------------------------------------------------------------------------------------
  void FontInstance::getLines(const std::string& text, float maxWidth, std::vector<std::string>& outputLines) const
  {
    if (m_height == 0 || text.empty())
    {
      return;
    }

    if (measureString(text).x <= maxWidth)
    {
      // If we are not in danger of running over the max width, we just split using the standard string utils function
      Celeste::split(text, outputLines);
      return;
    }

    float currentLineLength = 0;
    std::string currentSubLine;
    currentSubLine.reserve(text.size());

    for (char c : text)
    {
      if (c == '\n')
      {
        outputLines.push_back(currentSubLine);
        currentSubLine.clear();
        currentLineLength = 0;

        continue;
      }

      const Character* character = getCharacter(c);
      if (character == nullptr)
      {
        ASSERT_FAIL();
        continue;
      }

      if ((currentLineLength + character->m_advance) > maxWidth)
      {
        outputLines.push_back(currentSubLine);
        currentSubLine.clear();
        currentLineLength = 0;
      }

      currentSubLine.push_back(c);
      currentLineLength += character->m_advance;
    }

    outputLines.push_back(currentSubLine);
  }
}