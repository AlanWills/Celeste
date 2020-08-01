#include "OpenGL/GL.h"
#include "UtilityHeaders/GLHeaders.h"
#include "Log/Log.h"


namespace Celeste
{
  /// Initialize static variables
  bool GL::m_initialized = false;

  //------------------------------------------------------------------------------------------------
  bool GL::glfw_initialize()
  {
    if (!m_initialized)
    {
      int major = 0, minor = 0, revision = 0;
      glfwGetVersion(&major, &minor, &revision);
      
      Celeste::Log::info("glfw Min Major Version: 3");
      Celeste::Log::info("glfw Min Minor Version: 2");
      Celeste::Log::info("glfw Device Major Version: {0}", major);
      Celeste::Log::info("glfw Device Minor Version: {0}", minor);
      
#if GL_VERSION_3_0
      // If we have not yet initialized the glfw state, we do so now
      m_initialized = (glfwInit() == GLFW_TRUE);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
      glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
    }
#else
    LOG("OpenGL 3.0 not supported");
#endif

    ASSERT(m_initialized);
    return m_initialized;
  }

  //------------------------------------------------------------------------------------------------
  bool GL::glew_initialize()
  {
    bool result = true;

    // We don't ever have to exit glew so we don't have to worry about keeping track of it's initialization
    glewExperimental = GL_TRUE;
    result = (glewInit() == GLEW_OK);

    // Call it once to catch glewInit() bug, all other errors are now from our application.
    glGetError();
    result &= (glGetError() == GL_NO_ERROR); 

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