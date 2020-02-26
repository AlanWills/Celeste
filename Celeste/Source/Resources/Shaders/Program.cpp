#include "Resources/Shaders/Program.h"
#include "Resources/Shaders/VertexShader.h"
#include "Resources/Shaders/FragmentShader.h"
#include "Resources/ResourceManager.h"
#include "FileSystem/File.h"


namespace Celeste
{
  namespace Resources
  {
    //------------------------------------------------------------------------------------------------
    Program::Program() :
      m_programHandle(0),
      m_attributes(),
      m_uniforms()
    {
    }

    //------------------------------------------------------------------------------------------------
    Program::~Program()
    {
    }

    //------------------------------------------------------------------------------------------------
    GLuint Program::createFromFiles(const std::string& vertexShaderRelativePath, const std::string& fragmentShaderRelativePath)
    {
      if (m_programHandle > 0)
      {
        // Our program has already been created so just return our handle
        return m_programHandle;
      }

      // Vertex Shader
      observer_ptr<VertexShader> vShader = getResourceManager().load<VertexShader>(vertexShaderRelativePath);
      if (vShader == nullptr)
      {
        ASSERT_FAIL();
        return 0;
      }

      // Fragment Shader
      observer_ptr<FragmentShader> fShader = getResourceManager().load<FragmentShader>(fragmentShaderRelativePath);
      if (fShader == nullptr)
      {
        ASSERT_FAIL();
        return 0;
      }

      GLuint sVertex = vShader->create();
      GLuint sFragment = fShader->create();

      // Shader Program
      return create(sVertex, sFragment);
    }

    //------------------------------------------------------------------------------------------------
    GLuint Program::createFromCode(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
    {
      if (m_programHandle > 0)
      {
        // Our program has already been created so just return our handle
        return m_programHandle;
      }

      if (vertexShaderCode.empty() || fragmentShaderCode.empty())
      {
        ASSERT_FAIL();
        return 0;
      }

      VertexShader vShader;
      vShader.loadFromCode(vertexShaderCode);

      FragmentShader fShader;
      fShader.loadFromCode(fragmentShaderCode);

      GLuint sVertex = vShader.create();
      GLuint sFragment = fShader.create();

      // Shader Program
      return create(sVertex, sFragment);
    }

    //------------------------------------------------------------------------------------------------
    GLuint Program::create(GLuint vertexShaderHandle, GLuint fragmentShaderHandle)
    {
      if (vertexShaderHandle == 0 ||
          fragmentShaderHandle == 0)
      {
        ASSERT_FAIL();
        return 0;
      }

      // Shader Program
      m_programHandle = glCreateProgram();
      glAttachShader(m_programHandle, vertexShaderHandle);
      glAttachShader(m_programHandle, fragmentShaderHandle);

      glLinkProgram(m_programHandle);
      checkCompileErrors();

      // Delete the shaders as they're linked into our program now and no longer necessery
      glDeleteShader(vertexShaderHandle);
      glDeleteShader(fragmentShaderHandle);

      glCheckError();

      // Obtain attributes and uniforms
      getAttributeLocations();
      getUniformLocations();

      return m_programHandle;
    }

    //------------------------------------------------------------------------------------------------
    void Program::checkCompileErrors()
    {
      GLint success;
      glGetProgramiv(m_programHandle, GL_LINK_STATUS, &success);

      if (!success)
      {
        GLchar infoLog[1024];
        glGetProgramInfoLog(m_programHandle, 1024, nullptr, infoLog);

        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
        ASSERT_FAIL();
      }

      glCheckError();
    }

    //------------------------------------------------------------------------------------------------
    void Program::getAttributeLocations()
    {
      GLint i;
      GLint count;

      GLint size; // size of the variable
      GLenum type; // type of the variable (float, vec3 or mat4, etc)

      const GLsizei bufSize = 16; // maximum name length
      GLchar name[bufSize]; // variable name in GLSL
      GLsizei length; // name length

      glGetProgramiv(m_programHandle, GL_ACTIVE_ATTRIBUTES, &count);

      for (i = 0; i < count; i++)
      {
        glGetActiveAttrib(m_programHandle, (GLuint)i, bufSize, &length, &size, &type, name);
        m_attributes.insert(std::make_pair(std::string(name), glGetAttribLocation(m_programHandle, name)));
      }
    }

    //------------------------------------------------------------------------------------------------
    void Program::getUniformLocations()
    {
      GLint i;
      GLint count;

      GLint size; // size of the variable
      GLenum type; // type of the variable (float, vec3 or mat4, etc)

      const GLsizei bufSize = 16; // maximum name length
      GLchar name[bufSize]; // variable name in GLSL
      GLsizei length; // name length

      glGetProgramiv(m_programHandle, GL_ACTIVE_UNIFORMS, &count);

      for (i = 0; i < count; i++)
      {
        glGetActiveUniform(m_programHandle, (GLuint)i, bufSize, &length, &size, &type, name);
        m_uniforms.insert(std::make_pair(std::string(name), glGetUniformLocation(m_programHandle, name)));
      }
    }

    //------------------------------------------------------------------------------------------------
    void Program::destroy()
    {
      if (m_programHandle != 0 && glIsProgram(m_programHandle))
      {
        glDeleteProgram(m_programHandle);
        m_programHandle = 0;
      }

      m_attributes.clear();
      m_uniforms.clear();
    }

    //------------------------------------------------------------------------------------------------
    void Program::bind() const
    {
      if (m_programHandle > 0)
      {
        glUseProgram(m_programHandle);
      }
    }

    //------------------------------------------------------------------------------------------------
    void Program::setFloat(const GLchar *name, GLfloat value) const
    {
      glAssert(hasUniform(name));
      glUniform1f(m_uniforms.at(name), value);
      glCheckError();
    }

    //------------------------------------------------------------------------------------------------
    void Program::setInteger(const GLchar *name, GLint value) const
    {
      glAssert(hasUniform(name));
      glUniform1i(m_uniforms.at(name), value);
      glCheckError();
    }

    //------------------------------------------------------------------------------------------------
    void Program::setVector2f(const GLchar *name, GLfloat x, GLfloat y) const
    {
      glAssert(hasUniform(name));
      glUniform2f(m_uniforms.at(name), x, y);
      glCheckError();
    }

    //------------------------------------------------------------------------------------------------
    void Program::setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z) const
    {
      glAssert(hasUniform(name));
      glUniform3f(m_uniforms.at(name), x, y, z);
      glCheckError();
    }

    //------------------------------------------------------------------------------------------------
    void Program::setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const
    {
      glAssert(hasUniform(name));
      glUniform4f(m_uniforms.at(name), x, y, z, w);
      glCheckError();
    }

    //------------------------------------------------------------------------------------------------
    void Program::setMatrix4(const GLchar *name, const glm::mat4 &matrix) const
    {
      glAssert(hasUniform(name));
      setMatrix4(m_uniforms.at(name), matrix);
    }

    //------------------------------------------------------------------------------------------------
    void Program::setMatrix4(GLint location, const glm::mat4 &matrix) const
    {
      glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
      glCheckError();
    }
  }
}