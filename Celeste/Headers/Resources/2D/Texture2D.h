#pragma once

#include "CelesteDllExport.h"
#include "UtilityHeaders/GLHeaders.h"
#include "Resources/Resource.h"


namespace Celeste
{
  namespace Resources
  {
    // Texture2D is able to store and configure a texture in OpenGL.
    // It also hosts utility functions for easy management.
    class Texture2D : public Resource
    {
      public:
        // Constructor (sets default texture modes)
        CelesteDllExport Texture2D();
        CelesteDllExport ~Texture2D();

        // Binds the texture as the current active GL_TEXTURE_2D texture object
        CelesteDllExport void bind() const;
        CelesteDllExport void unbind() const;

        GLuint getInternalFormat() const { return m_internalFormat; }
        void setInternalFormat(GLuint internalFormat) { m_internalFormat = internalFormat; }

        GLuint getImageFormat() const { return m_imageFormat; }
        void setImageFormat(GLuint imageFormat) { m_imageFormat = imageFormat; }

        GLuint getWrapS() const { return m_wrap_S; }
        void setWrapS(GLuint wrapS) { m_wrap_S = wrapS; }

        GLuint getWrapT() const { return m_wrap_T; }
        void setWrapT(GLuint wrapT) { m_wrap_T = wrapT; }

        /// \brief Returns the width and height of the texture being rendered
        const glm::vec2& getDimensions() const { return m_dimensions; }

        // Generates texture from image data
        CelesteDllExport void generate(GLuint width, GLuint height, unsigned char* data);

        CelesteDllExport void setPixel(GLint x, GLint y, unsigned char* data);

      protected:
        CelesteDllExport bool doLoadFromFile(const Path& path) override;
        CelesteDllExport void doUnload() override;

        // Holds the ID of the texture object, used for all texture operations to reference to this particlar texture
        GLuint m_textureHandle;

      private:
        typedef Resource Inherited;

        // Texture image dimensions
        glm::vec2 m_dimensions;   // Width and height of loaded image in pixels

        // Texture Format
        GLuint m_internalFormat;     // Format of texture object
        GLuint m_imageFormat;        // Format of loaded image

        // Texture configuration
        GLuint m_wrap_S;              // Wrapping mode on S axis
        GLuint m_wrap_T;              // Wrapping mode on T axis
        GLuint m_filter_Min;          // Filtering mode if texture pixels < screen pixels
        GLuint m_filter_Max;          // Filtering mode if texture pixels > screen pixels
    };
  }
}