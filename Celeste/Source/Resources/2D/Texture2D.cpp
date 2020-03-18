#include "Resources/2D/Texture2D.h"
#include "Resources/2D/RawImageLoader.h"


namespace Celeste::Resources
{
  //------------------------------------------------------------------------------------------------
  Texture2D::Texture2D() :
    m_textureHandle(0),
    m_dimensions(),
    m_internalFormat(GL_RGBA),
    m_imageFormat(GL_RGBA),
    m_wrap_S(GL_REPEAT),
    m_wrap_T(GL_REPEAT),
    m_filter_Min(GL_LINEAR),
    m_filter_Max(GL_LINEAR)
  {
  }

  //------------------------------------------------------------------------------------------------
  Texture2D::~Texture2D()
  {
  }

  //------------------------------------------------------------------------------------------------
  bool Texture2D::doLoadFromFile(const Path& path)
  {
    setInternalFormat(GL_RGBA);
    setImageFormat(GL_RGBA);

    // Load the image - this will free the image data
    RawImageLoader loader(path);
    if (loader.getData() == nullptr)
    {
      return false;
    }

    // Now generate textureHandle
    generate(loader.getWidth(), loader.getHeight(), loader.getData());
    return true;
  }

  //------------------------------------------------------------------------------------------------
  void Texture2D::doUnload()
  {
    if (m_textureHandle > 0 && glIsTexture(m_textureHandle))
    {
      glDeleteTextures(1, &m_textureHandle);
      m_textureHandle = 0;
    }

    m_dimensions.x = 0;
    m_dimensions.y = 0;
    m_imageFormat = GL_RGBA;
    m_internalFormat = GL_RGBA;
  }

  //------------------------------------------------------------------------------------------------
  void Texture2D::generate(GLuint width, GLuint height, unsigned char* data)
  {
    m_dimensions.x = static_cast<float>(width);
    m_dimensions.y = static_cast<float>(height);

    glGenTextures(1, &m_textureHandle);

    // Check to see if there was a problem generating the texture
    if (m_textureHandle > 0)
    {
      // Create Texture
      bind();

      glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, width, height, 0, m_imageFormat, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);

      // Set Texture wrap and filter modes
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap_S);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap_T);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filter_Min);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filter_Max);

      // Unbind texture
      unbind();
    }
  }

  //------------------------------------------------------------------------------------------------
  void Texture2D::setPixel(GLint x, GLint y, unsigned char* data)
  {
    glTextureSubImage2DEXT(m_textureHandle, GL_TEXTURE_2D, 0, x, y, 1, 1, m_imageFormat, GL_UNSIGNED_BYTE, data);
  }

  //------------------------------------------------------------------------------------------------
  void Texture2D::bind() const
  {
    glBindTexture(GL_TEXTURE_2D, m_textureHandle);
    glCheckError();
  }

  //------------------------------------------------------------------------------------------------
  void Texture2D::unbind() const
  {
    glBindTexture(GL_TEXTURE_2D, 0);
    glCheckError();
  }
}