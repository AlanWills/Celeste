#include "Resources/Fonts/Font.h"
#include "Utils/StringUtils.h"


namespace Celeste::Resources
{
  //------------------------------------------------------------------------------------------------
  void Font::doUnload()
  {
    // Delete any existing textures
    for (const auto& characterPair : m_charactersLookup)
    {
      for (const std::pair<char, Character>& characters : characterPair.second)
      {
        if (glIsTexture(characters.second.m_textureId))
        {
          glDeleteTextures(1, &characters.second.m_textureId);
        }
      }
    }

    // Clear character arrays
    m_charactersLookup.clear();
  }

  //------------------------------------------------------------------------------------------------
  std::unique_ptr<FontInstance> Font::createInstance(float height)
  {
    if (height <= 0 || getResourceId() == "")
    {
      ASSERT_FAIL();
      return std::unique_ptr<FontInstance>();
    }

    loadCharacters(height);

    // Ensure the characters have been loaded
    ASSERT(m_charactersLookup.find(height) != m_charactersLookup.end());
    return std::unique_ptr<FontInstance>(new FontInstance(m_charactersLookup.at(height), height, *this));
  }

  //------------------------------------------------------------------------------------------------
  void Font::loadCharacters(float height)
  {
    if (m_charactersLookup.find(height) != m_charactersLookup.end())
    {
      // Characters have already been loaded, so we don't need to do anything here
      return;
    }

    if (height <= 0)
    {
      ASSERT_FAIL();
      return;
    }

    if (!File(getFilePath()).exists())
    {
      // If the file doesn't exist, we should return here
      ASSERT_FAIL();
      return;
    }

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
      ASSERT_FAIL();
      std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }

    FT_Face face;
    if (FT_New_Face(ft, getFilePath().c_str(), 0, &face))
    {
      ASSERT_FAIL();
      std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }

    FT_Set_Pixel_Sizes(face, 0, static_cast<FT_UInt>(height));
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

    Characters characters;

    for (GLubyte c = 0; c < 128; c++)
    {
      // Load character glyph 
      if (FT_Load_Char(face, c, FT_LOAD_RENDER))
      {
        ASSERT_FAIL();
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        continue;
      }

      // Generate texture
      GLuint texture;
      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);
      glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer
      );

      // Set texture options
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      // Since we only have one channel's worth of data we have to store it in the red component
      // However, we can fake the data to be read as the alpha channel by samplers in the shader
      // This allows us to render text and sprites using the same shaders
      GLint swizzleMask[] = { GL_ONE, GL_ONE, GL_ONE, GL_RED };
      glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);

      // Now store character for later use
      Character character = {
        texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        // Advance is stored in 1/64 (0.015625) of pixels so divide
        face->glyph->advance.x * 0.015625f
      };
      characters.insert(std::pair<GLchar, Character>(c, character));
    }

    m_charactersLookup.insert(std::make_pair(height, characters));

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // Enable byte-alignment restriction
  }
}