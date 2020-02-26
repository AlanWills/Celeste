#pragma once

#include "Resources/2D/Texture2D.h"


namespace CelesteTestUtils
{
  class MockTexture2D : public Celeste::Resources::Texture2D
  {
    public:
      ~MockTexture2D()
      {
        if (glIsTexture(m_textureHandle))
        {
          glDeleteTextures(1, &m_textureHandle);
        }
      }

      GLuint getTextureHandle() const { return m_textureHandle; }
  };
}