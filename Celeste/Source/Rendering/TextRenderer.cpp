#include "Rendering/TextRenderer.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Resources/ResourceManager.h"
#include "Input/InputManager.h"
#include "Utils/StringUtils.h"

using namespace Celeste::Resources;


namespace Celeste::Rendering
{
  REGISTER_UNMANAGED_COMPONENT(TextRenderer, 20)

  //------------------------------------------------------------------------------------------------
  TextRenderer::TextRenderer(GameObject& gameObject) :
    Inherited(gameObject),
    m_font(),
    m_lines(),
    m_dimensions()
  {
    setFont(Path("Fonts", "Arial.ttf"));
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::render(const Program& shaderProgram, const glm::mat4& viewModelMatrix) const
  {
    shaderProgram.setVector4f("colour", getColour());

    glm::vec2& halfTextSize = getDimensions() * 0.5f;
    const FontInstance& font = getFont();
    float fontHeight = font.getHeight();

    // Cache this location here so it's not evaluated for every letter
    GLint viewModelLocation = shaderProgram.getUniformLocation("view_model");

    for (size_t i = 0; i < m_lines.size(); ++i)
    {
      const std::string& line = m_lines[i];
      const glm::vec2& halfLineSize = font.measureString(line) * 0.5f;

      glm::mat4 letterRenderMatrix;
      letterRenderMatrix[3].x = getXPosition(halfLineSize.x);
      letterRenderMatrix[3].y = getYPosition(halfTextSize.y) - (i + 0.75f) * fontHeight; // Go down the screen - first text at the top

      for (char letter : line)
      {
        const Character* character = font.getCharacter(letter);
        if (!character)
        {
          ASSERT_FAIL();
          continue;
        }

        // Add on the character's bearing from the cursor
        letterRenderMatrix[3].x += character->m_bearing.x;

        if (character->m_size.x == 0 ||
          character->m_size.y == 0)
        {
          letterRenderMatrix[3].x += character->m_advance;
          continue;
        }

        letterRenderMatrix[0] *= character->m_size.x;
        letterRenderMatrix[1] *= character->m_size.y;

        //Shift down by the amount the letter lies underneath the line - bearing = amount above line and size = total height
        letterRenderMatrix[3].y += (character->m_bearing.y - character->m_size.y);

        //Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, character->m_textureId);

        //Render quad
        //We have to perform the letter render matrix first before applying the world space matrix, so that if there is a rotation
        //All of the text will rotate around one point rather than all the individual quads rotating
        shaderProgram.setMatrix4(viewModelLocation, viewModelMatrix * letterRenderMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Advance the cursor
        letterRenderMatrix[3].x += (character->m_advance - character->m_bearing.x);

        // Undo the character specific changes we made to our matrix
        letterRenderMatrix[3].y -= (character->m_bearing.y - character->m_size.y);
        letterRenderMatrix[0] /= (float)character->m_size.x; // Reset the scale
        letterRenderMatrix[1] /= (float)character->m_size.y; // Reset the scale
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::setFont(const std::string& relativePathToFont, float height)
  {
    observer_ptr<Font> font = getResourceManager().load<Font>(relativePathToFont);
    if (font == nullptr)
    {
      ASSERT_FAIL();
      return;
    }

    m_font = font->createInstance(height);
    recalculateDimensions();
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::recalculateDimensions()
  {
    m_dimensions.x = 0;
    m_dimensions.y = m_lines.size() * m_font.getHeight();

    for (const std::string& line : m_lines)
    {
      m_dimensions.x = (std::max)(m_dimensions.x, m_font.measureString(line).x);
    }
  }

#pragma region Text Manipulation Functions

  //------------------------------------------------------------------------------------------------
  void TextRenderer::setText(const std::string& text)
  {
    m_lines.clear();
    getLines(text, m_lines);
    recalculateDimensions();
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::clearLines()
  {
    m_lines.clear();
    m_dimensions = glm::vec2();
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::resetLines(const std::string& text)
  {
    m_lines.clear();
    addLine(text);
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::resetLines(const std::vector<std::string>& lines)
  {
    m_lines.clear();
    addLines(lines);
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::addLine(const std::string& lineText)
  {
    m_lines.push_back(lineText);
    recalculateDimensions();
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::addLines(const std::vector<std::string>& lines)
  {
    m_lines.insert(m_lines.end(), lines.begin(), lines.end());
    recalculateDimensions();
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::removeLine(size_t lineIndex)
  {
    if (lineIndex < m_lines.size())
    {
      // size_t so don't need to check >= 0
      m_lines.erase(m_lines.begin() + lineIndex);
      recalculateDimensions();
    }
    else
    {
      ASSERT_FAIL();
    }
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::setLine(size_t lineIndex, const std::string& text)
  {
    if (lineIndex < m_lines.size())
    {
      // size_t so don't need to check >= 0
      m_lines[lineIndex] = text;
      recalculateDimensions();
    }
    else
    {
      ASSERT_FAIL();
    }
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::getLine(size_t lineIndex, std::string& outLine) const
  {
    if (lineIndex < m_lines.size())
    {
      // size_t so don't need to check >= 0
      outLine.append(m_lines[lineIndex]);
    }
    else
    {
      ASSERT_FAIL();
    }
  }

  //------------------------------------------------------------------------------------------------
  std::string TextRenderer::getLine(size_t lineIndex) const
  {
    if (lineIndex < m_lines.size())
    {
      // size_t so don't need to check >= 0
      return m_lines[lineIndex];
    }
    else
    {
      ASSERT_FAIL();
      return "";
    }
  }

  //------------------------------------------------------------------------------------------------
  size_t TextRenderer::getLineLength(size_t lineIndex) const
  {
    if (lineIndex < m_lines.size())
    {
      // size_t so don't need to check >= 0
      return m_lines[lineIndex].size();
    }
    else
    {
      ASSERT_FAIL();
      return 0;
    }
  }

  //------------------------------------------------------------------------------------------------
  glm::vec2 TextRenderer::getLineDimensions(size_t lineIndex) const
  {
    if (lineIndex < m_lines.size())
    {
      // size_t so don't need to check >= 0
      return m_font.measureString(m_lines[lineIndex]);
    }
    else
    {
      ASSERT_FAIL();
      return glm::vec2();
    }
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::addLetter(size_t lineIndex, size_t letterIndex, char letter)
  {
    if (lineIndex >= m_lines.size() || letterIndex > m_lines[lineIndex].size())
    {
      // size_t so don't need to check >= 0
      // Strict inequality on letter index, because we want to be able to append to lines
      ASSERT_FAIL();
      return;
    }

    std::string& line = m_lines[lineIndex];
    if (letterIndex == line.size())
    {
      line.push_back(letter);
    }
    else
    {
      line.insert(line.begin() + letterIndex, letter);
    }

    recalculateDimensions();
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::removeLetter(size_t lineIndex, size_t letterIndex)
  {
    if (lineIndex >= m_lines.size() || letterIndex >= m_lines[lineIndex].size())
    {
      // size_t so don't need to check >= 0
      ASSERT_FAIL();
      return;
    }

    std::string& line = m_lines[lineIndex];
    if (letterIndex == line.size())
    {
      line.pop_back();
    }
    else
    {
      line.erase(line.begin() + letterIndex);
    }

    recalculateDimensions();
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::setLetter(size_t lineIndex, size_t letterIndex, char letter)
  {
    if (lineIndex >= m_lines.size() || letterIndex >= m_lines[lineIndex].size())
    {
      // size_t so don't need to check >= 0
      ASSERT_FAIL();
      return;
    }

    m_lines[lineIndex][letterIndex] = letter;
    recalculateDimensions();
  }

  //------------------------------------------------------------------------------------------------
  char TextRenderer::getLetter(size_t lineIndex, size_t letterIndex) const
  {
    if (lineIndex >= m_lines.size() || letterIndex >= m_lines[lineIndex].size())
    {
      // size_t so don't need to check >= 0
      ASSERT_FAIL();
      return (char)-1;
    }

    return m_lines[lineIndex][letterIndex];
  }

  //------------------------------------------------------------------------------------------------
  glm::vec2 TextRenderer::getLetterOffset(size_t lineIndex, size_t letterIndex) const
  {
    if (lineIndex >= m_lines.size() || letterIndex > m_lines[lineIndex].size())
    {
      // size_t so don't need to check >= 0
      // Strict inequality on letterIndex, because this corresponds to the length of the whole line
      // Need to be able to do this to allow setting the caret past the last letter
      ASSERT_FAIL();
      return glm::vec2();
    }

    const glm::vec2& measured = m_font.measureString(m_lines[lineIndex].substr(0, letterIndex));
    return glm::vec2(measured.x + getXPosition(getLineDimensions(lineIndex).x * 0.5f), getYPosition(m_lines.size() * getFontHeight() * 0.5f) - lineIndex * getFontHeight());
  }

#pragma endregion
}