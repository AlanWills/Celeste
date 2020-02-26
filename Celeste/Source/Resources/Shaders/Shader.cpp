#include "OpenGL/GL.h"
#include "Resources/Shaders/Shader.h"
#include "FileSystem/File.h"


namespace Celeste
{
  namespace Resources
  {
    //------------------------------------------------------------------------------------------------
    Shader::Shader() :
      m_shader(0)
    {
    }

    //------------------------------------------------------------------------------------------------
    Shader::~Shader()
    {
    }

    //------------------------------------------------------------------------------------------------
    void Shader::doUnload()
    {
      m_shaderSource.clear();

      if (m_shader != 0 && glIsShader(m_shader))
      {
        glDeleteShader(m_shader);
      }

      m_shader = 0;
    }

    //------------------------------------------------------------------------------------------------
    GLuint Shader::create()
    {
      if (m_shaderSource.empty())
      {
        ASSERT_FAIL();
        return 0;
      }

      if (m_shader != 0)
      {
        // If we have already created the shader, just return it
        return m_shader;
      }

      // Need this separate variable because glShaderSource needs lvalue
      const char* shaderSource_c = m_shaderSource.c_str();

      m_shader = GL::createShader(getShaderType());
      if (m_shader > 0)
      {
        glShaderSource(m_shader, 1, &shaderSource_c, nullptr);
        glCompileShader(m_shader);

        if (!checkCompileErrors() && glIsShader(m_shader))
        {
          glDeleteShader(m_shader);
          m_shader = 0;
        }
      }

      glCheckError();
      return m_shader;
    }

    //------------------------------------------------------------------------------------------------
    bool Shader::checkCompileErrors()
    {
      GLint success;
      glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);

      if (success == 0)
      {
        GLchar infoLog[1024];

        glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog);

        std::cout << "ERROR::SHADER::" << getShaderTypeString() << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        ASSERT_FAIL();
      }

      glCheckError();
      return success > 0;
    }
  }
}