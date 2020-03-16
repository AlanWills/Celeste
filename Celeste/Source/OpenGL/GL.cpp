#include "OpenGL/GL.h"
#include "UtilityHeaders/GLHeaders.h"
#include "Debug/Log.h"


namespace Celeste
{
  /// Initialize static variables
  bool GL::m_initialized = false;

  //------------------------------------------------------------------------------------------------
  bool GL::glfw_initialize()
  {
    bool result = true;
    
    if (!m_initialized)
    {
      int major = 0, minor = 0, revision = 0;
      glfwGetVersion(&major, &minor, &revision);
      
      LOG("glfw Major Version: " + std::to_string(major));
      LOG("glfw Minor Version: " + std::to_string(minor));
      
      if (GL_VERSION_3_0 || glewIsSupported("GL_VERSION_3_0"))
      {
        // If we have not yet initialized the glfw state, we do so now
        result = (glfwInit() == GLFW_TRUE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

        // Mark the state as now initialized
        m_initialized = true;
      }
      else
      {
        LOG("OpenGL 3.0 not supported");
      }
    }

    return result;
  }

  //------------------------------------------------------------------------------------------------
  bool GL::glew_initialize()
  {
    bool result = true;

    // We don't ever have to exit glew so we don't have to worry about keeping track of it's initialization
    glewExperimental = GL_TRUE;
    result = (glewInit() == GLEW_OK);
    result &= (glGetError() == GL_NO_ERROR); // Call it once to catch glewInit() bug, all other errors are now from our application.

    return result;
  }

  //------------------------------------------------------------------------------------------------
  bool GL::terminate()
  {
    if (m_initialized)
    {
      // If we have initialized the state, we exit it and clean it up now
      glfwTerminate();

      // Mark the state as now terminated
      m_initialized = false;
    }

    return true;
  }

  //------------------------------------------------------------------------------------------------
  bool GL::genBuffer(GLuint& outputBuffer)
  {
    if (!m_initialized)
    {
      return false;
    }

    glGenBuffers(1, &outputBuffer);
    return outputBuffer > 0;
  }

  //------------------------------------------------------------------------------------------------
  bool GL::isBuffer(GLuint buffer)
  {
    return m_initialized && buffer > 0 && glIsBuffer(buffer);
  }

  //------------------------------------------------------------------------------------------------
  void GL::deleteBuffer(GLuint buffer)
  {
    if (m_initialized)
    {
      glDeleteBuffers(1, &buffer);
    }
  }

  //------------------------------------------------------------------------------------------------
  bool GL::genVertexArray(GLuint& outputVertexArray)
  {
    if (!m_initialized)
    {
      return false;
    }

    glGenVertexArrays(1, &outputVertexArray);
    return outputVertexArray > 0;
  }

  //------------------------------------------------------------------------------------------------
  bool GL::isVertexArray(GLuint vertexArray)
  {
    return m_initialized && vertexArray > 0 && glIsVertexArray(vertexArray);
  }

  //------------------------------------------------------------------------------------------------
  void GL::deleteVertexArray(GLuint vertexArray)
  {
    if (m_initialized)
    {
      glDeleteVertexArrays(1, &vertexArray);
    }
  }

  //------------------------------------------------------------------------------------------------
  GLuint GL::createShader(GLenum shaderType)
  {
    return m_initialized ? glCreateShader(shaderType) : static_cast<GLuint>(0);
  }

  //------------------------------------------------------------------------------------------------
  bool GL::isShader(GLuint shader)
  {
    return m_initialized && shader > 0 && glIsShader(shader);
  }

  //------------------------------------------------------------------------------------------------
  void GL::deleteShader(GLuint shader)
  {
    if (m_initialized)
    {
      glDeleteShader(shader);
    }
  }

  //------------------------------------------------------------------------------------------------
  bool GL::isProgram(GLuint program)
  {
    return m_initialized && program > 0 && glIsProgram(program);
  }

  //------------------------------------------------------------------------------------------------
  void GL::deleteProgram(GLuint program)
  {
    if (m_initialized)
    {
      glDeleteProgram(program);
    }
  }
}