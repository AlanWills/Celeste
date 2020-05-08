#include "Rendering/TextRenderer.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Resources/ResourceManager.h"
#include "Input/InputManager.h"
#include "Utils/StringUtils.h"

using namespace Celeste::Resources;


namespace Celeste::Rendering
{
  REGISTER_COMPONENT(TextRenderer, 20)

  //------------------------------------------------------------------------------------------------
  TextRenderer::TextRenderer(GameObject& gameObject) :
    Inherited(gameObject),
    m_font(),
    m_text(),
    m_dimensions()
  {
    setFont(Path("Fonts", "Arial.ttf"));
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::render(const Program& shaderProgram, const glm::mat4& viewModelMatrix) const
  {
    shaderProgram.setVector4f("colour", getColour());

    glm::vec2 halfTextSize = getDimensions() * 0.5f;
    const FontInstance& font = getFont();
    float fontHeight = font.getHeight();

    // Cache this location here so it's not evaluated for every letter
    GLint viewModelLocation = shaderProgram.getUniformLocation("view_model");
    
    std::vector<std::string> lines;
    split(m_text, lines);

    for (size_t i = 0; i < lines.size(); ++i)
    {
      const std::string& line = lines[i];
      const glm::vec2& halfLineSize = font.measureString(line) * 0.5f;

      glm::mat4 letterRenderMatrix = glm::identity<glm::mat4>();
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

        letterRenderMatrix[0] *= static_cast<float>(character->m_size.x);
        letterRenderMatrix[1] *= static_cast<float>(character->m_size.y);

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
    std::vector<std::string> lines;
    split(m_text, lines);

    m_dimensions.x = 0;
    m_dimensions.y = lines.size() * m_font.getHeight();

    for (const std::string& line : lines)
    {
      m_dimensions.x = (std::max)(m_dimensions.x, m_font.measureString(line).x);
    }
  }

#pragma region Text Manipulation Functions

  //------------------------------------------------------------------------------------------------
  void TextRenderer::setHorizontalWrapMode(UI::HorizontalWrapMode horizontalWrapMode)
  { 
    m_horizontalWrapMode = horizontalWrapMode;

    if (m_horizontalWrapMode == UI::HorizontalWrapMode::kWrap && m_maxWidth > 0)
    {
      layoutText();
      recalculateDimensions();
    }
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::setMaxWidth(float maxWidth)
  {
    ASSERT(maxWidth > 0 || m_horizontalWrapMode != UI::HorizontalWrapMode::kWrap);
    m_maxWidth = maxWidth;

    if (m_horizontalWrapMode == UI::HorizontalWrapMode::kWrap)
    {
      layoutText();
      recalculateDimensions();
    }
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::layoutText()
  {
    ASSERT(m_maxWidth > 0);

    float currentWidth = 0;
    size_t currentOffset = 0;
    size_t nextOffset = m_text.find(' ');

    while (nextOffset < m_text.size())
    {
      float extraWidth = m_font.measureString(m_text.begin() + currentOffset, m_text.begin() + nextOffset).x;
      
      if (currentWidth + extraWidth > m_maxWidth)
      {
        // We have gone over our max width so we move the word to the next line
        m_text[currentOffset] = '\n';
        currentWidth = 0;
      }

      currentWidth += extraWidth;
      currentOffset = nextOffset;
      nextOffset = m_text.find(' ', currentOffset + 1);
    }
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::setText(const std::string& text)
  {
    if (m_text != text)
    {
      m_text.assign(text);

      if (m_horizontalWrapMode == UI::HorizontalWrapMode::kWrap && m_maxWidth > 0)
      {
        layoutText();
      }

      recalculateDimensions();
    }
  }

#pragma endregion
}