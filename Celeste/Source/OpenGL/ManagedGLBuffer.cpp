#include "OpenGL/ManagedGLBuffer.h"
#include "OpenGL/GL.h"


namespace Celeste
{
  namespace GLUtility
  {
    //------------------------------------------------------------------------------------------------
    ManagedGLBuffer::ManagedGLBuffer() :
      m_buffer(static_cast<GLuint>(0))
    {
    }

    //------------------------------------------------------------------------------------------------
    ManagedGLBuffer::~ManagedGLBuffer()
    {
      if (GL::isBuffer(m_buffer))
      {
        GL::deleteBuffer(m_buffer);
      }

      m_buffer = 0;
    }

    //------------------------------------------------------------------------------------------------
    ManagedGLBuffer::ManagedGLBuffer(ManagedGLBuffer&& rhs) noexcept :
      m_buffer(std::move(rhs.m_buffer))
    {
    }

    //------------------------------------------------------------------------------------------------
    bool ManagedGLBuffer::allocate()
    {
      return GL::genBuffer(m_buffer);
    }

    //------------------------------------------------------------------------------------------------
    bool ManagedGLBuffer::isValid() const
    {
      return m_buffer > 0 && GL::isBuffer(m_buffer);
    }
  }
}