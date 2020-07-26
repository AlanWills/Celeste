#pragma once

#include "CelesteDllExport.h"
#include "Character.h"
#include "StringId/string_id.h"

#include <unordered_map>


namespace Celeste::Resources
{
  class Font;

  class FontInstance
  {
    public:
      CelesteDllExport const Character* getCharacter(GLchar character) const;
      float getHeight() const { return m_height; }
      const Font& getFont() const { return m_font; }

      CelesteDllExport glm::vec2 measureString(std::string::const_iterator start, std::string::const_iterator end) const;
      CelesteDllExport glm::vec2 measureString(const std::string& text) const;
      CelesteDllExport void getLines(const std::string& text, float m_maxWidth, std::vector<std::string>& outputLines) const;

    protected:
      size_t getNumberOfCharacters() const { return m_characters.size(); }

    private:
      using Characters = std::unordered_map<GLchar, Character> ;

      /// Only create FontInstances through a Font class
      FontInstance(const Characters& fontCharacters, float height, const Font& font);

      Characters m_characters;
      float m_height;
      const Font& m_font;

      friend class Font;
  };
}