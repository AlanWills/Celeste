#pragma once

#include "CelesteDllExport.h"
#include "Character.h"
#include "UID/StringId.h"


namespace Celeste
{
  namespace Resources
  {
    class Font;

    class FontInstance
    {
      public:
        CelesteDllExport FontInstance();

        CelesteDllExport const Character* getCharacter(GLchar character) const;
        float getHeight() const { return m_height; }
        StringId getFontName() const { return m_fontName; }

        CelesteDllExport glm::vec2 measureString(const std::string& text) const;
        CelesteDllExport void getLines(const std::string& text, float m_maxWidth, std::vector<std::string>& outputLines) const;

        CelesteDllExport void reset();

      protected:
        size_t getNumberOfCharacters() const { return m_characters.size(); }

      private:
        typedef std::unordered_map<GLchar, Character> Characters;

        /// Only create FontInstances through a Font class
        FontInstance(const Characters& fontCharacters, float height, StringId fontName);

        Characters m_characters;
        float m_height;
        StringId m_fontName;

        friend class Font;
    };
  }
}