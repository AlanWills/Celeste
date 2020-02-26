#pragma once

#include "CelesteDllExport.h"
#include "UtilityHeaders/GLHeaders.h"


namespace Celeste
{
  namespace GLUtility
  {
    class CelesteDllExport ManagedGLBuffer
    {
      public:
        ManagedGLBuffer();
        ~ManagedGLBuffer();
        ManagedGLBuffer(ManagedGLBuffer&&) noexcept;

        // Delete these functions to avoid copying of GL buffer handles
        ManagedGLBuffer(const ManagedGLBuffer&) = delete;
        ManagedGLBuffer& operator=(const ManagedGLBuffer&) = delete;

        GLuint getBuffer() const { return m_buffer; }

        bool allocate();
        bool isValid() const;

      private:
        GLuint m_buffer;
    };
  }
}