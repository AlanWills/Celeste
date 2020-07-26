#pragma once

#include "UtilityHeaders/GLHeaders.h"
#include "OpenGL/GL.h"


namespace CelesteTestUtils
{
  class AutoGLDeallocator
  {
    public:
      AutoGLDeallocator(GLuint handle) :
        m_handle(handle)
      {
      }

      ~AutoGLDeallocator()
      {
        if (Celeste::GL::isProgram(m_handle))
        {
          Celeste::GL::deleteProgram(m_handle);
        }

        if (Celeste::GL::isShader(m_handle))
        {
          Celeste::GL::deleteShader(m_handle);
        }

        if (Celeste::GL::isBuffer(m_handle))
        {
          Celeste::GL::deleteBuffer(m_handle);
        }

        // VAO?
      }

    private:
      GLuint m_handle;
  };
}