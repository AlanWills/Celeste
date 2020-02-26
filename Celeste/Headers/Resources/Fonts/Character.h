#pragma once

#include "UtilityHeaders/GLHeaders.h"


namespace Celeste
{
  namespace Resources
  {
    struct Character
    {
      GLuint      m_textureId;    // ID handle of the glyph texture
      glm::ivec2  m_size;         // Size of glyph
      glm::ivec2  m_bearing;      // Offset from baseline to left/top of glyph
      float       m_advance;      // Offset to advance to next glyph
    };
  }
}