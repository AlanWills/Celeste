#pragma once

#include "Resources/Fonts/FontInstance.h"
#include "Renderer.h"
#include "UI/LayoutEnums.h"
#include "FileSystem/Path.h"


namespace Celeste::Rendering
{
  // A class which is responsible for rendering text in a specific font
  class TextRenderer : public Renderer
  {
    DECLARE_SCRIPT(TextRenderer, CelesteDllExport)

    public:
      CelesteDllExport void render(const Resources::Program& shaderProgram, const glm::mat4& viewModelMatrix) const override;

      /// Loads a font from the resource manager and sets it to be the font this renderer uses
      CelesteDllExport void setFont(const std::string& relativePathToFont, float height = 12);
      void setFont(const char* relativePathToFont, float height = 12) { setFont(std::string(relativePathToFont), height); }
      void setFont(const Path& relativePathToFont, float height = 12) { setFont(relativePathToFont.as_string(), height); }

      inline const Resources::FontInstance& getFont() const { return m_font; }

      void setFontHeight(float height) { setFont(deinternString(m_font.getFontName()), height); }
      inline float getFontHeight() const { return m_font.getHeight(); }

      inline glm::vec2 getDimensions() const override { return m_dimensions; }

      CelesteDllExport void setText(const std::string& text);

      /// Removes all lines from this renderer
      CelesteDllExport void clearLines();

      /// Clear all the current lines and add the inputted text
      CelesteDllExport void resetLines(const std::string& text = "");

      /// Clear all the current lines and add the inputted lines
      CelesteDllExport void resetLines(const std::vector<std::string>& lines);

      /// Add all the inputted lines
      CelesteDllExport void addLines(const std::vector<std::string>& lines);

      /// Add a new line with the inputted text
      CelesteDllExport void addLine(const std::string& lineText = "");

      /// Remove the line at the inputted index
      CelesteDllExport void removeLine(size_t lineIndex);

      /// Set the text of the line with the inputted index
      CelesteDllExport void setLine(size_t lineIndex, const std::string& text);

      /// Obtain the text of the line with the inputted index
      CelesteDllExport std::string getLine(size_t lineIndex) const;
      CelesteDllExport void getLine(size_t lineIndex, std::string& outLine) const;

      /// Get the number of lines in this renderer
      inline size_t getLineCount() const { return m_lines.size(); }

      /// Get the number of characters in the line with the inputted index
      CelesteDllExport size_t getLineLength(size_t lineIndex) const;

      /// Get the font measured dimensions of the line with the inputted index
      CelesteDllExport glm::vec2 getLineDimensions(size_t lineIndex) const;

      /// Add the inputted character to the inputted index in the line with the inputted line index
      CelesteDllExport void addLetter(size_t lineIndex, size_t letterIndex, char letter);

      /// Remove the letter at the inputted index from the line with the inputted line index
      CelesteDllExport void removeLetter(size_t lineIndex, size_t letterIndex);

      /// Set the letter at the inputted index in the line with the inputted line index
      CelesteDllExport void setLetter(size_t lineIndex, size_t letterIndex, char letter);

      /// Obtain the letter at the inputted index from the line with the inputted line index
      CelesteDllExport char getLetter(size_t lineIndex, size_t letterIndex) const;

      /// Obtain the offset from the origin of the inputted letter from the line with the inputted index
      /// Uses the alignment values
      CelesteDllExport glm::vec2 getLetterOffset(size_t lineIndex, size_t letterIndex) const;

      inline void setHorizontalAlignment(UI::HorizontalAlignment horizontalAlignment) { m_horizontalAlignment = horizontalAlignment; }
      inline UI::HorizontalAlignment getHorizontalAlignment() const { return m_horizontalAlignment; }

      inline void setVerticalAlignment(UI::VerticalAlignment verticalAlignment) { m_verticalAlignment = verticalAlignment; }
      inline UI::VerticalAlignment getVerticalAlignment() const { return m_verticalAlignment; }

    protected:
      inline float getXPosition(float halfLineWidth) const { return -static_cast<int>(m_horizontalAlignment)* halfLineWidth; }
      inline float getYPosition(float halfMaxHeight) const { return (2 - static_cast<int>(m_verticalAlignment))* halfMaxHeight; }

    private:
      using Inherited = Renderer;

      void recalculateDimensions();

      Resources::FontInstance m_font;
      std::vector<std::string> m_lines;

      UI::HorizontalAlignment m_horizontalAlignment = UI::HorizontalAlignment::kCentre;
      UI::VerticalAlignment m_verticalAlignment = UI::VerticalAlignment::kCentre;

      glm::vec2 m_dimensions;
  };
}